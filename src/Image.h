#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdint>
#include "GL/gl.h"

class Image {
    public:
        bool setImage(uint32_t* image);

        int width, height;
        GLuint texture;

};

#endif // IMAGE_H_
