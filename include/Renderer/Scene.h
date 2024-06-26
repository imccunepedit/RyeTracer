#ifndef SCENE_H_
#define SCENE_H_


#include <vector>
#include <memory>

#include <glm/vec4.hpp>

#include "Objects/Object.h"
#include "Materials/Material.h"

using namespace Rye::Objects;
using namespace Rye::Materials;

namespace Rye {
    class Ray;
    class HitData;

    class Scene {
        public:
            void AddObject(const ObjectTypes& o);
            void RemoveObject(int i);

            void AddMaterial(const MaterialTypes& m);
            void RemoveMaterial(int i);

            void CornellBox();
            void TestScene();
            void Box2();
            bool Hit(const Ray& ray, HitData& hit, float t_min) const;

            Material& GetMaterial(uint32_t ID);

        public:
            std::vector<Object> objects;

            size_t materialCount = 0;

            glm::vec4 ambientColor = glm::vec4(0);

            glm::vec4 lightDirection = glm::vec4(1,0,-1, 0);
            glm::vec4 lightColor = glm::vec4(1,0.8,0.6, 1);

        private:
            std::vector<Material> m_materials;
    };
}

#endif // SCENE_H_
