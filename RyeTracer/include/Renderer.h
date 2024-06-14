#ifndef RENDERER_H_
#define RENDERER_H_

#include "Scene.h"
#include "Camera.h"
#include "Ray.h"

#include "HitData.h"
#include "Material.h"

namespace Rye {
    class Renderer
    {
        public:
            Renderer(Camera* camera, Scene* scene) : m_camera(camera), m_scene(scene) {}

            void Render();

            void DrawControls();

        private:
            glm::vec4 RayGen(const int& i, const int& j);
            HitData TraceRay(const Ray& ray);
            HitData ClosestHit(const Ray& ray, HitData& hit);
            HitData Miss(const Ray& ray);

        private:
            Camera* m_camera = nullptr;
            Scene* m_scene = nullptr;

            int m_maxDepth = 5;
    };
}

#endif // RENDERER_H_
