#include "Film.h"


using namespace Barley;

void Film::Resize(const int& w, const int& h)
{
    accumulated.Resize(w, h);
    data.Resize(w, h);

    ResetAccumulator();
}

void Film::ResetAccumulator()
{
    samples = 0;
    accumulated.Clear();
}


uint32_t Film::ProcessColor(glm::vec3 color)
{
    color = glm::max(color, glm::vec3(0));
    if (gamma_correction)
        color = glm::sqrt(color);
    uint8_t r = fminf(color.r, 0.99999f)*256;
    uint8_t g = fminf(color.g, 0.99999f)*256;
    uint8_t b = fminf(color.b, 0.99999f)*256;
    uint8_t a = 255;
    return (a << 24) | (b << 16) | (g << 8) | r;
}
