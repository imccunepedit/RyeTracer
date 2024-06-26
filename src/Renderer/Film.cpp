#include "Renderer/Film.h"

#include <cstdint>
#include <cstring>

#include <glm/exponential.hpp>
#include <glm/ext/scalar_common.hpp>

using namespace Rye;

void Film::Resize(int w, int h)
{
    if(w*h <= 0)
        return;

    width = w;
    height = h;

    delete[] m_accumulated;
    m_accumulated = new glm::vec3[width*height];

    delete[] data;
    data = new glm::vec3[width*height];

    needsReset = true;
    ResetAccumulator();
}

void Film::ResetAccumulator()
{
    if (!needsReset)
        return;
    if (width*height <= 1)
        return;

    needsReset = false;
    m_samples = 0;
    std::memset(m_accumulated, 0, width*height*sizeof(glm::vec3));
}

void Film::SetPixel(int index, const glm::vec3& color)
{
    m_accumulated[index] += color;
    data[index] = ProcessColor(m_accumulated[index]);
}


glm::vec3 Film::ProcessColor(glm::vec3 color)
{
    color = color * m_samplesInverse;
    color = glm::max(color, glm::vec3(0));
    color = glm::sqrt(color);

    return color;
}
