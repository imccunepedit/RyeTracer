#ifndef RENDERER_H_
#define RENDERER_H_

#include <glm/vec3.hpp>

namespace Rye {
    class Camera;
    class Scene;
    class Ray;
    class HitData;


    class Renderer
    {
        public:
            Renderer(Camera* camera, Scene* scene) : m_camera(camera), m_scene(scene) {}

            int Render();

            void DrawControls();

        private:
            glm::vec3 RayGen(int i);
            HitData TraceRay(const Ray& ray, HitData& hit);
            HitData ClosestHit(const Ray& ray, HitData& hit) const;
            HitData Miss(const Ray& ray, HitData& hit) const;

        private:
            Camera* m_camera = nullptr;
            Scene* m_scene = nullptr;
            bool m_debug = false;
            bool m_viewNormals = false;
            bool m_absNormals = false;

            int m_maxDepth = 10; // could do less if there isn't any glass or different scene with glass
    };
}

#endif // RENDERER_H_
