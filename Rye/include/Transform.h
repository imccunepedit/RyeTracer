#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/vec3.hpp>

class Transform
{
    public:
        Transform() = default;
        Transform(glm::vec3 p) : position(p) {}
        Transform(float p) : position(glm::vec3(p)) {}
        Transform(glm::vec3 p, float s) : position(p), scale(glm::vec3(s)) {}

        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);
};

#endif /* TRANSFORM_H_ */
