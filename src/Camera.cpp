#include <cstdint>
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <iostream>

#include <glm/glm.hpp>
#include <GL/gl.h>

#include "Camera.h"
#include "Ray.h"
#include "Hit.h"

#define PI 3.14159
float convert_to_rads (float angle) {
    return angle / 180 * PI;
}

void Camera::render(Scene &s, Image* image) {
    initialize(image);
    uint32_t* image_data = new uint32_t[image->width*image->height];
    for (int j=0; j < image->height; j++) {
        for (int i = 0; i < image->width; i++) {
            Ray r = get_ray(i, j);
            glm::vec4 pixel_color = trace_ray(r, s);
            image_data[i + j*image->width] = convert_color(pixel_color);
        }
    }

    image->setImage(image_data);
}



glm::vec4 Camera::trace_ray(Ray &r, Scene &s) {
    // Sphere sp = Sphere({4,0,0},1,{1,0,0,1});

    // Hit h = sp.hit(r);
    // if (h.t > 0 ) {
    //     return sp.color;
    // }

    // return s.sky_color;


    if (s.spheres.size() == 0) return s.sky_color;
    Hit closest_hit;
    Sphere* closest_sphere = nullptr;
    closest_hit.t = max_distance;
    for (int i = 0; i < s.spheres.size(); i++) {
        Sphere sphere = s.spheres.at(i);
        Hit hit = sphere.hit(r);
        if (hit.t < min_distance) {
            continue;
        }

        if (closest_sphere == nullptr) {
            closest_hit = hit;
            closest_sphere = &sphere;
        } else if (hit.t < closest_hit.t) {
            closest_hit = hit;
            closest_sphere = &sphere;
        }

    }

    if (closest_sphere != nullptr) {
        return closest_sphere->color;
        std::cout << closest_sphere->color.b << "\n";
    }
    return s.sky_color;

}


uint32_t Camera::convert_color(glm::vec4 color) {
    color = glm::clamp(color, glm::vec4(0), glm::vec4(1));
    int r = color.r*255;
    int g = color.g*255;
    int b = color.b*255;
    int a = color.a*255;
    return (a << 24) | (b << 16) | (g << 8) | r;
}

Ray Camera::get_ray(int x, int y) {
    // TODO for some reason the direction converges towards 1,0,0 each render
    glm::vec3 pixel = viewport_origin + float(x) * viewport_du + float(y) * viewport_dv;
    glm::vec3 direction = glm::normalize(pixel - position);
    return Ray(position, direction);
}


void Camera::initialize(Image* image) {

    // if (initialized) {
    //     return;
    // }
    // initialized = true;

    aspect_ratio = float(image->width) / image->height;

    viewport_width = tan(convert_to_rads(fov)/2.0) * focal_dist * 2;
    viewport_height = viewport_width / aspect_ratio;

    viewport_u = viewport_width * right;
    viewport_v = -viewport_height * up;

    viewport_du = viewport_u/float(image->width);
    viewport_dv = viewport_v/float(image->height);

    viewport_origin = (position + forward*focal_dist) - 0.5f*viewport_v - 0.5f*viewport_u;
}
