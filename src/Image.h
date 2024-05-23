#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdint>
#include "GL/gl.h"
#include "imgui.h"

class Image {
    public:
        bool set_image(uint32_t* image);
        void draw_image();

        int window_width, window_height;
        int width, height;
        ImTextureID texture_id;

    private:
        GLuint texture;

};

#endif // IMAGE_H_
