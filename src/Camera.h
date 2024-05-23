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
        void calculate_camera_directions();
        void calculate_viewport_size(Image* image);

        void render(const Scene &scene, Image* image);
        void draw_controls(const char& title);

    private:
        uint32_t per_pixel(int& x, int& y, const Scene& scene);
        Ray get_ray(int& x, int& y);
        glm::vec4 trace_ray(const Ray &ray, const Scene &scene, int bounces);
        uint32_t process_color(const glm::vec4& color);




    public:
        int max_depth = 1; // max depth into scene
        int rays_per_pixel = 1;
        glm::vec3 position = glm::vec3(0,0,0);
        glm::vec3 local_up = glm::vec3(0,0,1);
        glm::vec3 local_forward = glm::vec3(1,0,0);
        glm::vec3 viewport_origin; //top left of top left pixel

    // private:
        float aspect_ratio;
        float focal_dist = 1.0;
        float fov = 90;


        glm::vec3 local_right = glm::cross(local_up, local_forward);

        float viewport_width, viewport_height;
        glm::vec3 viewport_u, viewport_v;
        glm::vec3 viewport_du, viewport_dv;


};


#endif // CAMERA_H_
