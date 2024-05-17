#ifndef CAMERA_H_
#define CAMERA_H_

#include <cstdint>
#include "GL/gl.h"

class Camera {
    public:
        void Render(GLuint* out_texture, int width, int height);
};


#endif // CAMERA_H_
