#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdint>
#include <glm/vec4.hpp>

namespace Barley {
    class Image {
        public:
            void Resize(const int& w, const int& h);
            void Clear();

            int Width() { return m_width; }
            int Height() { return m_height; }

        public:
            glm::vec4* data;

        private:
            int m_width, m_height;

    };
}
#endif // IMAGE_H_
