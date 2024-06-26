#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdint>
#include <string>

#include <glad/glad.h>

#include <glm/vec3.hpp>

namespace Rye::UI {
    class Image {
        public:
            void Set(glm::vec3* data);
            void Resize();
            void Draw();
            void BindImage() {
                glBindImageTexture(0, m_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
            }

        private:
            void Reset();

        public:
            int width=1;
            int height=1;
            std::string name= "Viewport";
            bool needsUpdate = false;

        private:
            GLuint m_texture;

    };
}
#endif // IMAGE_H_
