#include <cstdint>
#include <iostream>

#include <oneapi/tbb/parallel_for.h>

#include <GL/gl.h>

#include "Camera.h"
#include "Hit.h"
#include "Random.h"

#include "GLFW/glfw3.h"

#include "tracy/Tracy.hpp"


void Camera::initialize(Image *image)
{
    if (initialized)
        return;

    initialized = true;
    out_image = image;
    resize();
    calculate_camera_directions();
    calculate_viewport_vectors();
}

void Camera::render(const Scene &s)
{
    ZoneScoped;
    // initilize our camera with the info from our output image

#define MT
#ifdef MT
    oneapi::tbb::parallel_for(size_t(0), size_t(viewport_pixel_height), [this,s](size_t j)
    {
        oneapi::tbb::parallel_for(size_t(0), size_t(viewport_pixel_width), [this,s,j](size_t i){
            per_pixel(i, j, s);
        });
    });

#else
    for (int j=0; j < viewport_pixel_height; j++)
    {
        for (int i = 0; i < viewport_pixel_width; i++)
        {
            per_pixel(i, j, s);
        }
    }
#endif

    out_image->set_image(image_data);
    frame_index ++;
}

void Camera::per_pixel(int x, int y, const Scene &scene)
{
    ZoneScoped;

    // generate an offset so we cover more of our pixels area with rays
    uint32_t seed = x + y * viewport_pixel_width + out_image->texture*7919;

    seed *= frame_index;
    glm::vec3 offset = viewport_du*raytracing::random::random_float(seed) + viewport_dv*raytracing::random::random_float(seed);

    glm::vec3 pixel = viewport_origin + offset + float(x) * viewport_du + float(y) * viewport_dv;
    glm::vec3 direction = glm::normalize(pixel - position);
    Ray ray = Ray(position, direction);

    // glm::vec3 color = trace_ray(ray, scene, max_depth);
    accumulation_data[x + y *viewport_pixel_width] += trace_ray(ray, scene, max_depth, seed);

    glm::vec3 color = accumulation_data[x+y*viewport_pixel_width] / (float)frame_index;
    image_data[x + y*viewport_pixel_width] = process_color(color);
}

glm::vec3 Camera::trace_ray(const Ray &ray, const Scene &scene, int depth, uint32_t& rseed)
{
    ZoneScoped;
    if (depth < 1)
        return glm::vec3(0.0f);

    Hit hit;
    bool is_hit = scene.hit(ray, hit);

    if (!is_hit)
        return hit.light;

    float offset = 0.001f;

    Ray next_ray = Ray(hit.point + hit.normal * offset, hit.normal + raytracing::random::random_on_sphere(rseed));
    glm::vec3 bounced_light = trace_ray(next_ray, scene, depth-1, rseed);

    next_ray.direction = -scene.directional_light_direction;
    Hit light_hit;

    is_hit = scene.hit(next_ray, light_hit);
    glm::vec3 light = glm::vec3(0.0f);
    if (!is_hit)
    {
        light = scene.directional_light_color * fmaxf(glm::dot(hit.normal, -glm::normalize(scene.directional_light_direction)), 0.f);
    }

    return hit.light * (bounced_light + light);

}


uint32_t Camera::process_color(glm::vec3 color)
{
    color = glm::clamp(color, glm::vec3(0), glm::vec3(0.99999));
    if (gamma_correction)
        color = glm::sqrt(color);
    uint8_t r = color.r*255;
    uint8_t g = color.g*255;
    uint8_t b = color.b*255;
    uint8_t a = 255;
    return (a << 24) | (b << 16) | (g << 8) | r;
}


void Camera::reset_accumulator()
{
    frame_index = 1;
    memset(accumulation_data, 0, viewport_pixel_width*viewport_pixel_height*sizeof(glm::vec3));
}


void Camera::calculate_camera_directions()
{
    w = glm::normalize(-look_dir); // -forward
    u = glm::normalize(glm::cross(up,w));
    v = glm::cross(w,u);

}


void Camera::resize()
{
    if (out_image->height == viewport_pixel_height && out_image->width == viewport_pixel_width)
        return;

    viewport_pixel_height = out_image->height;
    viewport_pixel_width = out_image->width;

    delete[] image_data;
    image_data = new uint32_t[viewport_pixel_width*viewport_pixel_height];

    delete[] accumulation_data;
    accumulation_data = new glm::vec3[viewport_pixel_width*viewport_pixel_height];

    reset_accumulator();
}


void Camera::calculate_viewport_vectors()
{
    float aspect_ratio = float(viewport_pixel_width) / viewport_pixel_height;

    float viewport_world_width = tan(glm::radians(fov) * 0.5f) * focal_dist * 2;
    float viewport_world_height = viewport_world_width * 1.0f / aspect_ratio;

    glm::vec3 viewport_u = viewport_world_width * u;
    glm::vec3 viewport_v = -viewport_world_height * v;

    viewport_du = viewport_u/float(viewport_pixel_width);
    viewport_dv = viewport_v/float(viewport_pixel_height);

    viewport_origin = (position - w*focal_dist) - 0.5f*viewport_v - 0.5f*viewport_u;
}


void Camera::rotate(GLFWwindow* window, float delta)
{

    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        mouse_first = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        return;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    if (mouse_first)
    {
        glfwGetCursorPos(window, &mouse_position.x, &mouse_position.y);
        mouse_first = false;
    }

    last_mouse_position = mouse_position;

    glfwGetCursorPos(window, &mouse_position.x, &mouse_position.y);

    glm::vec2 mouse_delta = mouse_position - last_mouse_position;

    if (glm::dot(mouse_delta, mouse_delta) < 0.01)
        return;

    glm::vec2 sensitivity(-0.1f);

    look_dir = glm::rotateZ(look_dir, mouse_delta.x * sensitivity.x*delta);

    calculate_camera_directions();
    calculate_viewport_vectors();
    reset_accumulator();
}

void Camera::move(GLFWwindow* window, float delta)
{

    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
        return;
    float speed = 4;
    bool has_moved = false;

    if (glfwGetKey(window, GLFW_KEY_W))
    {
        has_moved = true;
        position += -w*speed*delta;
    }
    else if (glfwGetKey(window, GLFW_KEY_S))
    {
        has_moved = true;
        position += w*speed*delta;
    }
    if (glfwGetKey(window, GLFW_KEY_D))
    {
        has_moved = true;
        position += u*speed*delta;
    }
    else if (glfwGetKey(window, GLFW_KEY_A))
    {
        has_moved = true;
        position += -u*speed*delta;
    }


    if (has_moved)
    {
        reset_accumulator();
        calculate_viewport_vectors();
    }

}




void Camera::debug_window()
{
    ImGui::Begin("Camera Debug", NULL, ImGuiWindowFlags_NoCollapse);
    ImGui::Text("u (right):       % f, % f, % f", u.x, u.y, u.z);
    ImGui::Text("v (up):          % f, % f, % f", v.x, v.y, v.z);
    ImGui::Text("w (backwards):   % f, % f, % f", w.x, w.y, w.z);
    ImGui::Separator();
    ImGui::Text("Viewport origin: % f, % f, % f", viewport_origin.x, viewport_origin.y, viewport_origin.z);
    ImGui::Text("Viewport du:     % f, % f, % f", viewport_du.x, viewport_du.y, viewport_du.z);
    ImGui::Text("Viewport dv:     % f, % f, % f", viewport_dv.x, viewport_dv.y, viewport_dv.z);
    ImGui::Separator();
    // ImGui::Text("Viewport size:   % f, % f", viewport_width, viewport_height);
    ImGui::Text("Focal dist:      % f", focal_dist);
    ImGui::Text("Horizontal fov:  % f", fov);
    ImGui::End();
}
