#ifndef OBJECT_H_
#define OBJECT_H_

#include <glm/vec4.hpp>

#include "Ray.h"
#include "HitData.h"

class Object {
    public:
        virtual bool Hit(const Ray& ray, HitData& hit) const { return false; }
        virtual bool DrawAttributes() { return false; }

    protected:
        glm::vec4 m_position = glm::vec4(0);
        uint32_t m_materialID = 0;
};

#endif // OBJECT_H_
