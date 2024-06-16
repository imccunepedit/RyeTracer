#include "Film.h"

#include <cstdint>
#include <cstring>

#include <glm/exponential.hpp>
#include <glm/ext/scalar_common.hpp>

using namespace Rye;

void Film::Resize(const int& w, const int& h)
{
    if(w*h <= 0)
        return;

    width = w;
    height = h;

    delete[] m_accumulated;
    m_accumulated = new glm::vec4[width*height];

    delete[] data;
    data = new glm::vec4[width*height];

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
    std::memset(m_accumulated, 0, width*height*sizeof(glm::vec4));
}

void Film::SetPixel(const int& index, const glm::vec4& color)
{
    m_accumulated[index] += color;
    data[index] = ProcessColor(m_accumulated[index]);
}


glm::vec4 Film::ProcessColor(glm::vec4 color)
{
    color = color * m_samplesInverse;
    color = glm::max(color, glm::vec4(0));
    color = glm::sqrt(color);

    return color;
}
