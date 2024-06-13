#ifndef FILM_H_
#define FILM_H_

#include "Image.h"

#include <glm/vec4.hpp>

namespace Barley {
    class Film
    {
        public:
            void SetPixel(const int& i, const int& j, const glm::vec4& color);
            void Resize(const int& w, const int& h);
            void ResetAccumulator();

            uint32_t ProcessColor(glm::vec4 color);

            int Width() { return m_data.Width(); }
            int Height() { return m_data.Height(); }

        public:
            int samples = 0;
        private:
            Image m_accumulated;
            Image m_data;

    };
}

#endif // FILM_H_
