#include "Renderer/Film.h"

#include <cstdint>
#include <cstring>

#include <glm/exponential.hpp>
#include <glm/ext/scalar_common.hpp>

using namespace Rye;

void Film::Resize(int w, int h)
{
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

void Film::SetPixel(int index, glm::vec3& color)
{

    if (!std::isfinite(color.r))
        color.r = 0.0f;
    if (!std::isfinite(color.g))
        color.g = 0.0f;
    if (!std::isfinite(color.b))
        color.b = 0.0f;

    m_accumulated[index] += glm::clamp(color, glm::vec3(0), glm::vec3(10));
    data[index] = ProcessColor(m_accumulated[index]);
}


glm::vec3 Film::ProcessColor(glm::vec3 color)
{
    color = color * m_samplesInverse;
    color = glm::max(color, glm::vec3(0));
    color = glm::sqrt(color);

    return color;
}
