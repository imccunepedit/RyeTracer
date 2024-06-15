#include "Film.h"

#include <cstdint>

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
    data = new uint32_t[width*height];

    ResetAccumulator();
}

void Film::ResetAccumulator()
{
    if (width*height <= 1)
        return;
    m_samples = 0;
    std::memset(m_accumulated, 0, width*height*sizeof(glm::vec4));
}

void Film::SetPixel(const int& index, const glm::vec4& color)
{
    m_accumulated[index] += color;
    data[index] = ProcessColor(m_accumulated[index]);
}


uint32_t Film::ProcessColor(glm::vec4 color)
{
    color = color * m_samplesInverse;
    color = glm::max(color, glm::vec4(0));
    color = glm::sqrt(color);

    uint8_t r = fminf(color.r, 0.99999f)*256;
    uint8_t g = fminf(color.g, 0.99999f)*256;
    uint8_t b = fminf(color.b, 0.99999f)*256;
    uint8_t a = 255;

    return (a << 24) | (b << 16) | (g << 8) | r;
}
