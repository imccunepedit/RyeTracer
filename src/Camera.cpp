#include <cmath>
#include <cstdint>
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <iostream>

#include <glm/glm.hpp>
#include "GL/gl.h"

#include "Camera.h"
#include "Ray.h"

void Camera::render() {
    initialize();
    uint32_t* image_data = new uint32_t[image->width*image->height];
    for (int j=0; j < image->height; j++) {
        for (int i = 0; i < image->width; i++) {
            Ray r = get_ray(i, j);
            glm::vec4 pixel_color = trace_ray(r);
            image_data[i + j*image->width] = convert_color(pixel_color);
        }
    }

    image->setImage(image_data);
}


glm::vec4 Camera::trace_ray(Ray r) {
    glm::dvec3 center = glm::dvec3(4,0,0);
    double radius = 1;

    double a = glm::dot(r.direction, r.direction);
    double b = -2.0 * glm::dot(r.direction, center - r.origin);
    double c = glm::dot(center - r.origin,center - r.origin) - radius * radius;

    double discriminant = b*b - 4*a*c;
    double t = -1.0;

    if (discriminant >= 0) {
        t = (-b - std::sqrt(discriminant)) / (2*a);
    }

    if (t > 0) {
        return glm::vec4(r.at(t) - center, 1)*0.5f + glm::vec4(0.5);
    }
    return sky_color;




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
    glm::dvec3 pixel = viewport_origin + double(x) * viewport_du + double(y) * viewport_dv;
    glm::dvec3 direction = pixel - position;
    return Ray(position, direction);
}


void Camera::initialize() {
    aspect_ratio = double(image->width) / image->height;

    viewport_width = tan(fov/2.0) * focal_dist * 2;
    viewport_height = viewport_width / aspect_ratio;

    viewport_u = viewport_width* right;
    viewport_v = -viewport_height * up;

    viewport_du = viewport_u/double(image->width);
    viewport_dv = viewport_v/double(image->height);

    viewport_origin = forward*focal_dist - 0.5*viewport_v - 0.5*viewport_u;
}
