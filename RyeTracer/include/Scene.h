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
            void AddObject(std::shared_ptr<Object> o);
            void RemoveObject(const int& i);

            void AddMaterial(std::shared_ptr<Material> m);
            void RemoveMaterial(const int& i);

            void Initialize();
            bool Hit(const Ray& ray, HitData& hit) const;

        public:
            std::vector<std::shared_ptr<Object>> objects;
            std::vector<std::shared_ptr<Material>> materials;
            size_t materialCount = 0;

            glm::vec4 ambientColor = glm::vec4(0);

            glm::vec4 lightDirection = glm::vec4(1,0,-1, 0);
            glm::vec4 lightColor = glm::vec4(1,0.8,0.6, 1);
    };
}

#endif // SCENE_H_
