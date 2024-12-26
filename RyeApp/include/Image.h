#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdint>
#include <string>

#include <vulkan/vulkan.h>

#include <glm/vec4.hpp>

namespace Barley {
    class Image {
        public:
            void Set(glm::vec4* data);
            void Resize();
            void Draw();
            void BindImage(); // tell the gpu to use our image for inout

        private:
            void Reset();

        public:
            int width=1;
            int height=1;
            std::string name= "Viewport";
            bool needsUpdate = false;

        private:
            // GLuint m_texture; // texture id

    };
}
#endif // IMAGE_H_
