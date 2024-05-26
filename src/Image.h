#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdint>
#include "GL/gl.h"
#include "imgui.h"

class Image {
    public:
        bool set_image(uint32_t* image);
        void draw_image();

        int width_last, height_last;
        int width, height;
        GLuint texture;

};

#endif // IMAGE_H_
