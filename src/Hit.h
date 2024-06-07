#ifndef HIT_H_
#define HIT_H_

#include "glm/vec3.hpp"

#include "Material.h"

struct Hit {
    glm::vec3 point;
    glm::vec3 normal;
    glm::vec3 color;
    float distance = std::numeric_limits<float>::max();
    bool inside = false;
    uint32_t rseed = 1; // sometimes we need to generate random values, seems to be an easy enough way to pass the seed forward
    uint32_t material_id = 0;

    Material material;
};

#endif // HIT_H_
