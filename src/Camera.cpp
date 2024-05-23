#include <cstdint>
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <iostream>

#include <GL/gl.h>

#include "Camera.h"
#include "Ray.h"
#include "Hit.h"

void Camera::render(const Scene &s, Image* image) {
    // initilize our camera with the info from our output image
    calculate_viewport_size(image);
    uint32_t* image_data = new uint32_t[image->width*image->height];
    for (int j=0; j < image->height; j++) {
        for (int i = 0; i < image->width; i++) {
            image_data[i + j*image->width] = per_pixel(i, j, s);
        }
    }
    image->set_image(image_data);
}

uint32_t Camera::per_pixel(int& x, int& y, const Scene &scene) {
    glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    for (int i = 0; i < rays_per_pixel; i++)
    {
        Ray ray = get_ray(x, y);
        color += trace_ray(ray, scene, max_depth);
    }

    return process_color(color);

    color /= float(rays_per_pixel);

}

glm::vec4 Camera::trace_ray(const Ray &ray, const Scene &scene, int depth) {
    if (depth < 1)
    {
        return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }

    Hit hit = scene.hit(ray);

    return hit.color;

    // if we haven't hit anything return what should be the sky color
    if (std::isinf(hit.distance))
        return hit.color;

    // Ray bounced_ray = Ray(hit.point, glm::reflect(ray.direction, hit.normal));

    glm::vec4 color = hit.color;

    // color += 0.5f * trace_ray(bounced_ray, scene, depth-1);

}


uint32_t Camera::process_color(const glm::vec4& color) {
    glm::vec4 ncolor = glm::clamp(color, glm::vec4(0), glm::vec4(1));
    int r = ncolor.r*255;
    int g = ncolor.g*255;
    int b = ncolor.b*255;
    int a = 255;
    return (a << 24) | (b << 16) | (g << 8) | r;
}

Ray Camera::get_ray(int& x, int& y) {
    // generate an offset so we cover more of our pixels area with rays
    // glm::vec3 offset =  glm::linearRand(glm::vec3(0.0f), viewport_du + viewport_dv);
    glm::vec3 offset = glm::vec3(0.0f);

    glm::vec3 pixel = viewport_origin + offset + float(x) * viewport_du + float(y) * viewport_dv;
    glm::vec3 direction = glm::normalize(pixel - position);
    return Ray(position, direction);
}


void Camera::calculate_viewport_size(Image* image) {

    aspect_ratio = float(image->width) / image->height;


    viewport_width = tan(glm::radians(fov)/2.0) * focal_dist * 2;
    viewport_height = viewport_width / aspect_ratio;

    viewport_u = viewport_width * local_right;
    viewport_v = -viewport_height * local_up;

    viewport_du = viewport_u/float(image->width);
    viewport_dv = viewport_v/float(image->height);

    viewport_origin = (position + local_forward*focal_dist) - 0.5f*viewport_v - 0.5f*viewport_u;
}
