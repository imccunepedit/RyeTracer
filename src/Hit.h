#ifndef HIT_H_
#define HIT_H_

#include "glm/glm.hpp"

class Hit {
    public:
        glm::dvec3 point;
        glm::dvec3 normal;
        double t;
};

#endif // HIT_H_
