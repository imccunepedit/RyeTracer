#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <glm/vec3.hpp>

class Material {
    public:
        glm::vec3 diffuse = glm::vec3(0.5f);
        glm::vec3 emissive = glm::vec3(0.0f);
        float emissive_strength = 0.0f;

};

#endif // MATERIAL_H_
