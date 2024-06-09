#ifndef HIT_H_
#define HIT_H_

#include "glm/vec3.hpp"

struct Hit {
    glm::vec3 point;
    glm::vec3 normal;
    glm::vec3 color = glm::vec3(0);
    float distance = std::numeric_limits<float>::max();
    bool inside = false;
    uint32_t material_id = 0;

};

#endif // HIT_H_
