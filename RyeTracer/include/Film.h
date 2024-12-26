#ifndef FILM_H_
#define FILM_H_

#include <glm/vec4.hpp>

namespace Rye {
    class Film
    {
        public:
            void SetPixel(const int& index, const glm::vec4& color);
            void Resize(const int& w, const int& h);
            void ResetAccumulator();
            void NewSample() {
                m_samples ++;
                m_samplesInverse = 1.0f/m_samples;
            };

            int Samples() { return m_samples; }

            glm::vec4 ProcessColor(glm::vec4 color);

        public:
            int width = 1;
            int height = 1;
            glm::vec4* data = nullptr;
            bool needsReset = true;

        private:
            int m_samples = 0;
            float m_samplesInverse;
            glm::vec4* m_accumulated = nullptr;

    };
}

#endif // FILM_H_
