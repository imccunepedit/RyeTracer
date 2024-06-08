#ifndef OBJECT_H_
#define OBJECT_H_

#include "Ray.h"
#include "Hit.h"

class Object {
    public:
        virtual bool hit(const Ray& ray, Hit& hit) const { return false; }
        virtual bool draw_attributes() { return false; }
        glm::vec3 position = glm::vec3(0.0f);
        uint32_t material_id = 0;
};

#endif // OBJECT_H_
