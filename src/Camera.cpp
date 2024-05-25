#include <cstdint>
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <iostream>

#include <oneapi/tbb/parallel_for.h>

#include <GL/gl.h>

#include "Camera.h"
#include "Ray.h"
#include "Hit.h"
#include "Random.h"

#include "tracy/Tracy.hpp"



void Camera::render(const Scene &s, Image* image)
{
    ZoneScoped;
    // initilize our camera with the info from our output image
    calculate_viewport_size(image);

#if 0
    for (int j=0; j < viewport_pixel_height; j++)
    {
        for (int i = 0; i < viewport_pixel_width; i++)
        {
            // std::cout << i + j* viewport_pixel_width << "\n";
            per_pixel(i, j, s);
        }
    }

#else

    oneapi::tbb::parallel_for(size_t(0), size_t(viewport_pixel_height), [this,s](size_t j)
    {
        oneapi::tbb::parallel_for(size_t(0), size_t(viewport_pixel_width), [this,s,j](size_t i){
            per_pixel(i, j, s);
        });
    });


#endif

    image->set_image(image_data);
    frame_index ++;
}

void Camera::per_pixel(int x, int y, const Scene &scene)
{
    ZoneScoped;

    // generate an offset so we cover more of our pixels area with rays
    uint32_t seed = x + y * viewport_pixel_width;

    seed *= frame_index;
    glm::vec3 offset = viewport_du*utils::random_float(seed) + viewport_dv*utils::random_float(seed);

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

    Ray next_ray = Ray(hit.point + hit.normal * offset, hit.normal + utils::random_on_sphere(rseed));
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
    if (use_look_at)
        w = glm::normalize(position-look_point);
    else
        w = glm::normalize(-look_dir);

    u = glm::normalize(glm::cross(up,w));
    v = glm::cross(w,u);

}


void Camera::calculate_viewport_size(Image* image)
{
    ZoneScoped;

    if (viewport_pixel_width == image->width &&
        viewport_pixel_height == image->height)
            return;


    viewport_pixel_height = image->height;
    viewport_pixel_width = image->width;


    delete[] accumulation_data;
    accumulation_data = new glm::vec3[viewport_pixel_width*viewport_pixel_height];
    reset_accumulator();

    delete[] image_data;
    image_data = new uint32_t[viewport_pixel_width*viewport_pixel_height];

    aspect_ratio = float(viewport_pixel_width) / viewport_pixel_height;

    viewport_width = tan(glm::radians(fov) * 0.5f) * focal_dist * 2;
    viewport_height = viewport_width * 1.0f / aspect_ratio;

    calculate_camera_directions();

    viewport_u = viewport_width * u;
    viewport_v = -viewport_height * v;

    viewport_du = viewport_u/float(viewport_pixel_width);
    viewport_dv = viewport_v/float(viewport_pixel_height);

    viewport_origin = (position - w*focal_dist) - 0.5f*viewport_v - 0.5f*viewport_u;
}


void Camera::debug_window()
{
    ImGui::Begin("Camera Debug");
    ImGui::Text("u (right):       % f, % f, % f", u.x, u.y, u.z);
    ImGui::Text("v (up):          % f, % f, % f", v.x, v.y, v.z);
    ImGui::Text("w (backwards):   % f, % f, % f", w.x, w.y, w.z);
    ImGui::Separator();
    ImGui::Text("Viewport origin: % f, % f, % f", viewport_origin.x, viewport_origin.y, viewport_origin.z);
    ImGui::Text("Viewport du:     % f, % f, % f", viewport_du.x, viewport_du.y, viewport_du.z);
    ImGui::Text("Viewport dv:     % f, % f, % f", viewport_dv.x, viewport_dv.y, viewport_dv.z);
    ImGui::Separator();
    ImGui::Text("Viewport size:   % f, % f", viewport_width, viewport_height);
    ImGui::Text("Focal dist:      % f", focal_dist);
    ImGui::Text("Horizontal fov:  % f", fov);
    ImGui::End();
}
