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

        public:
            int samples = 0;
            int width = 1;
            int height = 1;
            uint32_t* data = nullptr;

        private:
            glm::vec4* m_accumulated = nullptr;

    };
}

#endif // FILM_H_
