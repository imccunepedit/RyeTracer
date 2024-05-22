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
    initialize(image);
    uint32_t* image_data = new uint32_t[image->width*image->height];
    for (int j=0; j < image->height; j++) {
        for (int i = 0; i < image->width; i++) {
            glm::vec4 pixel_color = per_pixel(i, j, s);
            image_data[i + j*image->width] = process_color(pixel_color);
        }
    }
    image->setImage(image_data);
}

glm::vec4 Camera::per_pixel(int& x, int& y, const Scene &s) {
    glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    for (int i = 0; i < rays_per_pixel; i++)
    {
        Ray r = get_ray(x, y);
        color += trace_ray(r, s, max_bounces);
    }
    return color / float(rays_per_pixel);
}

glm::vec4 Camera::trace_ray(const Ray &r, const Scene &s, int bounces) {
    // testing
    // Sphere sp = Sphere({4,0,0},1,{1,0,0,1});

    // Hit h = sp.hit(r);
    // if (h.t > 0 ) {
    //     return sp.color;
    // }

    // return s.sky_color;


    // if we are at max depth just return
    if (bounces < 1)
    {
        return glm::vec4(0.0f);
    }

    // if there isn't anything in the scene return skycolor
    if (s.spheres.size() == 0)
    {
        return s.sky_color;
    }

    // try and find our closeset hit, loop over spheres
    Hit closest_hit;
    bool has_hit = false;
    closest_hit.t = max_distance;
    for (int i = 0; i < s.spheres.size(); i++)
    {
        Sphere sphere = s.spheres.at(i);
        Hit hit = sphere.hit(r);
        if (hit.t < min_distance)
        {
            continue;
        }

        if (!has_hit)
        {
            closest_hit = hit;
            has_hit = true;
        }
        else if (hit.t < closest_hit.t)
        {
            closest_hit = hit;
        }

    }

    // if we have hit anything then calculate new rays
    if (has_hit)
    {
        // glm::vec4 color =  glm::vec4(closest_hit.normal*0.5f+0.5f, 1);
        glm::vec4 color = closest_hit.color;
        glm::vec3 dir = glm::sphericalRand(1.0);
        if (glm::dot(dir, closest_hit.normal) < 0)
        {
            dir *= -1.0;
        }
        float hit_offset = 0.0001f;
        glm::vec3 bounce_origin = closest_hit.point + closest_hit.normal * hit_offset;
        Ray bounce_ray = Ray(closest_hit.point, dir);
        color += 0.5f * trace_ray(bounce_ray, s, bounces-1);
        return color;
        // / glm::vec4(bounces,bounces,bounces, 1);
        // std::cout << closest_sphere->color.b << "\n";

    }

    return s.sky_color;

}


uint32_t Camera::process_color(glm::vec4 color) {
    color = glm::clamp(color, glm::vec4(0), glm::vec4(1));
    int r = color.r*255;
    int g = color.g*255;
    int b = color.b*255;
    int a = color.a*255;
    return (a << 24) | (b << 16) | (g << 8) | r;
}

Ray Camera::get_ray(int& x, int& y) {
    glm::vec3 offset =  glm::linearRand(glm::vec3(0.0f), viewport_du + viewport_dv);
    glm::vec3 pixel = viewport_origin + offset + float(x) * viewport_du + float(y) * viewport_dv;
    glm::vec3 direction = glm::normalize(pixel - position);
    return Ray(position, direction);
}


void Camera::initialize(Image* image) {

    // if (initialized) {
    //     return;
    // }
    // initialized = true;

    aspect_ratio = float(image->width) / image->height;


    viewport_width = tan(glm::radians(fov)/2.0) * focal_dist * 2;
    viewport_height = viewport_width / aspect_ratio;

    viewport_u = viewport_width * right;
    viewport_v = -viewport_height * up;

    viewport_du = viewport_u/float(image->width);
    viewport_dv = viewport_v/float(image->height);

    viewport_origin = (position + forward*focal_dist) - 0.5f*viewport_v - 0.5f*viewport_u;
}
