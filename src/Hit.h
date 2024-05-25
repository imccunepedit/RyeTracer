#ifndef HIT_H_
#define HIT_H_

#include "glm/vec3.hpp"

class Hit {
    public:
        glm::vec3 point;
        glm::vec3 normal;
        glm::vec3 light;
        float distance = std::numeric_limits<float>::max();
};

#endif // HIT_H_
