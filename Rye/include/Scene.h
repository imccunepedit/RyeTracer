#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <memory>

#include <glm/vec4.hpp>


namespace Rye {
    class Object;
    class Material;
    class Ray;
    class HitData;

    class Scene {
        public:
            void AddObject(Object o);
            void RemoveObject(const int& i);

            void AddMaterial(Material m);
            void RemoveMaterial(const int& i);

            void Initialize();
            bool Hit(const Ray& ray, HitData& hit);

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
