#ifndef HIT_H_
#define HIT_H_

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

class Hit {
    public:
        glm::vec3 point;
        glm::vec3 normal;
        glm::vec4 color;
        float distance = std::numeric_limits<float>::infinity();
};

#endif // HIT_H_
