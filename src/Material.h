#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <glm/vec4.hpp>

class Material {
    public:
        Material (glm::vec4 c) : diffuse(c) {}
        glm::vec4 diffuse = glm::vec4(0.5f);
};

#endif // MATERIAL_H_
