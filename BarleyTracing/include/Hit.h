#ifndef HIT_H_
#define HIT_H_

#include "glm/vec4.hpp"

struct Hit {
    glm::vec4 point;
    glm::vec4 normal;
    glm::vec4 color = glm::vec4(0);
    float distance = std::numeric_limits<float>::max();
    bool inside = false;
    uint32_t material_id = 0;

};

#endif // HIT_H_
