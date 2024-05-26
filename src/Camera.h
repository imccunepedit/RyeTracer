#ifndef CAMERA_H_
#define CAMERA_H_

#include <GLFW/glfw3.h>
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
        void render(const Scene &scene);
        void initialize(Image* image);

        void resize();
        void calculate_camera_directions();
        void calculate_viewport_vectors();
        void reset_accumulator();

        void debug_window();
        void move(GLFWwindow* window, float delta);
        void rotate(GLFWwindow* window, float delta);

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
        // glm::vec3 look_point = glm::vec3(0,1,0);
        glm::vec3 look_dir = glm::vec3(0,1,0);
        float focal_dist = 1.0;

        bool gamma_correction = true;

    private:
        bool initialized = false;

        glm::vec3 v,u,w;
        float fov = 90;

        uint32_t frame_index = 1;

        int viewport_pixel_width = 0;
        int viewport_pixel_height = 0;

        glm::vec3 viewport_origin; //top left of top left pixel
        glm::vec3 viewport_du, viewport_dv;
        // glm::vec3 viewport_u, viewport_v;

        Image* out_image;
        uint32_t* image_data = nullptr;
        glm::vec3* accumulation_data = nullptr;
};


#endif // CAMERA_H_
