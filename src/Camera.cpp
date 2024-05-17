#include "Camera.h"
#include <cstdint>
#include "GL/gl.h"

void Camera::Render(GLuint* out_texture, int image_width, int image_height) {
    uint32_t* image_data = new uint32_t[image_width*image_height];
    for (int j=0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {

            uint32_t result = 0xFF000000;
            // if (j % 10 == 0 )
            //     result = 0xFF0000FF;
            // if (i % 10 == 0)
            //     result = 0xFFFF0000;

            int r = i/double(image_width) * 256;
            int g = j/double(image_height) * 256;
            int b = 0;
            int a = 255;
            result = (a << 24) | (b << 16) | (g << 8) | r;
            image_data[i + j*image_width] = result;
        }
    }


    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, image_data);

    *out_texture = image_texture;
}
