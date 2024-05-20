#ifndef HIT_H_
#define HIT_H_

#include "glm/glm.hpp"

class Hit {
    public:
        glm::vec3 point;
        glm::vec3 normal;
        float t;
};

#endif // HIT_H_
