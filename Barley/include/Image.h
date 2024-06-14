#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdint>
#include <cstring>

#include <glm/vec4.hpp>

namespace Barley {

    class Image {
        public:
            void Set();
            void Draw();

            int Width() { return m_width; }
            int Height() { return m_height; }

        private:
            int m_width, m_height;

    };
}
#endif // IMAGE_H_
