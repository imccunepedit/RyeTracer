#include "Film.h"

#include <glm/exponential.hpp>
#include <glm/ext/scalar_common.hpp>


using namespace Barley;

void Film::Resize(const int& w, const int& h)
{
    m_accumulated.Resize(w, h);
    m_data.Resize(w, h);

    ResetAccumulator();
}

void Film::ResetAccumulator()
{
    samples = 0;
    m_accumulated.Clear();
}

void Film::SetPixel(const int& i, const int& j, const glm::vec4& color)
{
    m_accumulated.data[i+j*Width()] += color;

    m_data.data[i+j*Width()] = m_accumulated.data[i+j*Width()] / (float)samples;
}


uint32_t Film::ProcessColor(glm::vec4 color)
{
    color = glm::max(color, glm::vec4(0));
    color = glm::sqrt(color);

    uint8_t r = fminf(color.r, 0.99999f)*256;
    uint8_t g = fminf(color.g, 0.99999f)*256;
    uint8_t b = fminf(color.b, 0.99999f)*256;
    uint8_t a = 255;

    return (a << 24) | (b << 16) | (g << 8) | r;
}
