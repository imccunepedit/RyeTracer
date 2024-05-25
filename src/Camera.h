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
        void debug_window();

        void render(const Scene &scene, Image* image);
        void reset_accumulator();

    private:
        void per_pixel(int x, int y, const Scene& scene);
        Ray get_ray(int x, int y);
        glm::vec3 trace_ray(const Ray &ray, const Scene &scene, int depth, uint32_t& rseed);
        uint32_t process_color(glm::vec3 color);


    public:
        int max_depth = 50; // max depth into scene
        int rays_per_pixel = 1;

        glm::vec3 position = glm::vec3(0,0,0);
        glm::vec3 up = glm::vec3(0,0,1);
        glm::vec3 look_point = glm::vec3(0,1,0);
        glm::vec3 look_dir = glm::vec3(0,1,0);
        float focal_dist = 1.0;

        bool gamma_correction = true;

        bool use_look_at = true;

    private:
        glm::vec3 v,u,w;
        float aspect_ratio;
        float fov = 90;

        uint32_t frame_index = 1;

        glm::vec3 viewport_origin; //top left of top left pixel
        int viewport_pixel_width = 0;
        int viewport_pixel_height = 0;
        float viewport_width, viewport_height;
        glm::vec3 viewport_u, viewport_v;
        glm::vec3 viewport_du, viewport_dv;

        uint32_t* image_data = nullptr;
        glm::vec3* accumulation_data = nullptr;
};


#endif // CAMERA_H_
