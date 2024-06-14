#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdint>
#include <cstring>

#include <GL/gl.h>

#include <glm/vec4.hpp>

namespace Barley {
    class Image {
        public:
            void Set(uint32_t* data);
            void ReSize();
            void Draw();

            int width=1;
            int height=1;

        private:
            GLuint m_texture;

    };
}
#endif // IMAGE_H_
