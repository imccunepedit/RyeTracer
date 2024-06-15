#ifndef HIT_H_
#define HIT_H_

#include <memory>

#include "glm/vec4.hpp"


namespace Rye {

    class Material;

    struct HitData {
        glm::vec4 point;
        glm::vec4 normal;
        glm::vec4 color = glm::vec4(0,0,0,1);
        float distance = std::numeric_limits<float>::max();
        bool front = true;
        std::shared_ptr<Material> material = nullptr;

        uint32_t seed = 1;
    };
}

#endif // HIT_H_
