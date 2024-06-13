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

        private:
            int m_width, m_height;
            glm::vec4* data;

    };
}
#endif // IMAGE_H_
