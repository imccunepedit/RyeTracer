#ifndef CAMERA_H_
#define CAMERA_H_

#include <cstdint>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include "GL/gl.h"
#include "Image.h"
#include "Ray.h"

class Camera {
    public:
        void set_output(Image* iimage) {
            image = iimage;
        }
        void render();

    private:
        void initialize();
        glm::vec4 rayColor(Ray r);
        uint32_t convertColor(glm::vec4 color);




    public:
        Image* image;
        glm::vec4 sky_color = glm::vec4(1.0);

    private:
        double aspect_ratio;
        double dist = 1.0;
        double fov = 3.14/2;

        glm::dvec3 position = glm::dvec3(0,0,0);
        glm::dvec3 up = glm::dvec3(0,0,1);
        glm::dvec3 forward = glm::dvec3(1,0,0);
        glm::dvec3 right = glm::cross(up, forward);

        double viewport_width, viewport_height;
        glm::dvec3 viewport_u, viewport_v;
        glm::dvec3 viewport_du, viewport_dv;
        glm::dvec3 viewport_origin;


};


#endif // CAMERA_H_
