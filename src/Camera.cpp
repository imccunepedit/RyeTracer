#include <cstdint>
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
            glm::dvec3 pixel = viewport_origin + double(i) * viewport_du + double(j) * viewport_dv;
            glm::dvec3 direction = pixel - position;
            Ray r(pixel, direction);
            glm::vec4 pixel_color = rayColor(r);
            image_data[i + j*image->width] = convertColor(pixel_color);
        }
    }

    image->setImage(image_data);
}


glm::vec4 Camera::rayColor(Ray r) {
    return sky_color;
}


uint32_t Camera::convertColor(glm::vec4 color) {
    int r = color.r*255;
    int g = color.g*255;
    int b = color.b*255;
    int a = color.a*255;
    return (a << 24) | (b << 16) | (g << 8) | r;
}



void Camera::initialize() {
    aspect_ratio = double(image->width) / image->height;

    viewport_width = tan(fov/2.0) * dist * 2;
    viewport_height = viewport_width / aspect_ratio;

    viewport_u = viewport_width* right;
    viewport_v = -viewport_height * up;

    viewport_du = viewport_u/double(image->width);
    viewport_dv = viewport_v/double(image->height);

    viewport_origin = forward*dist - 0.5*viewport_v - 0.5*viewport_u;
}
