#include <cstdint>
#include <iostream>

#include <oneapi/tbb/parallel_for.h>

#include <GL/gl.h>

#include "Camera.h"
#include "Hit.h"
#include "Random.h"

#include "GLFW/glfw3.h"

#include "tracy/Tracy.hpp"

#include <glm/gtc/quaternion.hpp>


void Camera::recalulate_all(Image *image)
{
    out_image = image;
    resize();
    calculate_view();
    calculate_projection();
    reset_accumulator();
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
            per_color(i, j, s);
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

void Camera::per_color(int x, int y, const Scene &scene)
{
    ZoneScoped;

    // generate an offset so we cover more of our pixels area with rays
    uint32_t seed = x + y * viewport_pixel_width + out_image->texture*7919;
    seed *= frame_index;

    glm::vec2 ray_screen_target = glm::vec2((x + raytracing::random_float(seed))/viewport_pixel_width,
                                           (y + raytracing::random_float(seed))/viewport_pixel_height) * 2.0f - 1.0f;

    glm::vec4 ray_world_target = inv_projection * glm::vec4(ray_screen_target, 1, 1);
    glm::vec3 ray_world_direction = glm::normalize(glm::vec3(inv_view * ray_world_target));

    Ray ray = Ray(position, ray_world_direction);

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
        return hit.material.emissive;

    float offset = 0.001f;

    Ray next_ray = Ray(hit.point + hit.normal * offset, hit.normal + raytracing::random_on_sphere(rseed));
    if (raytracing::random_float(rseed) > hit.material.roughness)
        next_ray.direction = glm::reflect(ray.direction, hit.normal);

    glm::vec3 bounced_light = trace_ray(next_ray, scene, depth-1, rseed);

    next_ray.direction = -scene.directional_light_direction;
    Hit light_hit;

    is_hit = scene.hit(next_ray, light_hit);
    glm::vec3 light = glm::vec3(0.0f);
    if (!is_hit)
    {
        light = hit.material.roughness*scene.directional_light_color * fmaxf(glm::dot(hit.normal, -glm::normalize(scene.directional_light_direction)), 0.f);
    }

    return hit.material.diffuse * (bounced_light + light) + hit.material.emissive*hit.material.emissive_strength;

}


uint32_t Camera::process_color(glm::vec3 color)
{
    color = glm::max(color, glm::vec3(0));
    if (gamma_correction)
        color = glm::sqrt(color);
    uint8_t r = fminf(color.r, 0.99999f)*256;
    uint8_t g = fminf(color.g, 0.99999f)*256;
    uint8_t b = fminf(color.b, 0.99999f)*256;
    uint8_t a = 255;
    return (a << 24) | (b << 16) | (g << 8) | r;
}


void Camera::reset_accumulator()
{
    frame_index = 1;
    memset(accumulation_data, 0, viewport_pixel_width*viewport_pixel_height*sizeof(glm::vec3));
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

void Camera::calculate_view()
{
    view = glm::lookAt(position, position+forward, up);
    inv_view = glm::inverse(view);

    right = glm::vec3(view[0][0], view[1][0], view[2][0]);
}




void Camera::calculate_projection()
{
    float aspect = 1.0f;
    if (viewport_pixel_height*viewport_pixel_width > 0.001f)
        aspect = viewport_pixel_width/(float)viewport_pixel_height;

    projection = glm::perspective(glm::radians(vfov), aspect, 0.1f, 100.0f);
    inv_projection = glm::inverse(projection);

}


void Camera::move(GLFWwindow* window, float time_delta)
{

    last_mouse_position = mouse_position;

    glfwGetCursorPos(window, &mouse_position.x, &mouse_position.y);

    glm::vec2 mouse_delta = mouse_position - last_mouse_position;

    if (!(ImGui::IsMouseDown(ImGuiMouseButton_Right)))
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        return;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);


    bool has_moved = false;

    if (glm::dot(mouse_delta, mouse_delta) > 0.0f)
    {

        forward = forward * glm::angleAxis(mouse_delta.y*sensitivity.y*time_delta, right);
        forward = forward * glm::angleAxis(mouse_delta.x*sensitivity.x*time_delta, up);

        has_moved = true;
    }


    // if (glfwGetKey(window, GLFW_KEY_W))
    glm::vec3 translate = glm::vec3(0);
    if (ImGui::IsKeyDown(ImGuiKey_W))
    {
        position += forward*speed*time_delta;
        has_moved = true;
    }
    if (ImGui::IsKeyDown(ImGuiKey_S))
    {
        position += -forward*speed*time_delta;
        has_moved = true;
    }
    if (ImGui::IsKeyDown(ImGuiKey_D))
    {
        position += right*speed*time_delta;
        has_moved = true;
    }
    if (ImGui::IsKeyDown(ImGuiKey_A))
    {
        position += -right*speed*time_delta;
        has_moved = true;
    }
    if (ImGui::IsKeyDown(ImGuiKey_E))
    {
        position += up*speed*time_delta;
        has_moved = true;
    }
    if (ImGui::IsKeyDown(ImGuiKey_Q))
    {
        position += -up*speed*time_delta;
        has_moved = true;
    }

    if (has_moved)
    {
        reset_accumulator();
        calculate_view();
        calculate_projection();
    }

}




void Camera::debug_window()
{
    ImGui::Begin("Camera Debug", NULL, ImGuiWindowFlags_NoCollapse);
    // ImGui::Text("Viewport size:   % f, % f", viewport_width, viewport_height);
    ImGui::Text("vertical fov:  % f", vfov);
    ImGui::End();
}
