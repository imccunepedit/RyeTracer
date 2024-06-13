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

            int Width() { return data.Width(); }
            int Height() { return data.Height(); }

        public:
            int samples = 0;
        private:
            Image accumulated;
            Image data;

    };
}

#endif // FILM_H_
