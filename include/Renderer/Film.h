#ifndef FILM_H_
#define FILM_H_

#include <glm/vec3.hpp>

namespace Rye {
    class Film
    {
        public:
            void SetPixel(int index, const glm::vec3& color);
            void Resize(int w, int h);
            void ResetAccumulator();
            void NewSample() {
                m_samples ++;
                m_samplesInverse = 1.0f/m_samples;
            };

            int Samples() const { return m_samples; }

            glm::vec3 ProcessColor(glm::vec3 color);

        public:
            int width = 1;
            int height = 1;
            glm::vec3* data = nullptr;
            bool needsReset = true;

        private:
            int m_samples = 0;
            float m_samplesInverse;
            glm::vec3* m_accumulated = nullptr;

    };
}

#endif // FILM_H_
