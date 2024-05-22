#ifndef CAMERA_H_
#define CAMERA_H_

#include <cstdint>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/random.hpp>

#include <GL/gl.h>

#include "Image.h"
#include "Ray.h"
#include "Sphere.h"
#include "Scene.h"

class Camera {
    public:
        void render(const Scene &scene, Image* image);

        void initialize(Image* image);

    private:
        glm::vec4 per_pixel(int& x, int& y, const Scene& s);
        Ray get_ray(int& x, int& y);
        glm::vec4 trace_ray(const Ray &r, const Scene &s, int bounces);
        uint32_t process_color(glm::vec4 color);




    public:
        float max_distance = 1.0e+10;
        float min_distance = 1.0e-2;
        int max_bounces = 10;
        int rays_per_pixel = 1;
        glm::vec3 position = glm::vec3(0,0,0);
        glm::vec3 up = glm::vec3(0,0,1);
        glm::vec3 forward = glm::vec3(1,0,0);
        glm::vec3 viewport_origin;

    // private:
        bool initialized = false;
        float aspect_ratio;
        float focal_dist = 1.0;
        float fov = 90;


        glm::vec3 right = glm::cross(up, forward);

        float viewport_width, viewport_height;
        glm::vec3 viewport_u, viewport_v;
        glm::vec3 viewport_du, viewport_dv;


};


#endif // CAMERA_H_
