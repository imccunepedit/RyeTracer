#include "Image.h"

#include <cstring>

using namespace Barley;

void Image::Resize(const int& w, const int& h)
{
    m_width = w;
    m_height = h;

    delete[] data;
    data = new glm::vec4[w*h];
}

void Image::Clear()
{
    std::memset(data, 0, m_width*m_height*sizeof(glm::vec4));
}
