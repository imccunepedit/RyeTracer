#ifndef RENDERER_H_
#define RENDERER_H_

#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "HitData.h"

namespace Barley {

    class Renderer
    {
        public:
            Renderer(Camera& camera, Scene& scene) : m_camera(camera), m_scene(scene) {}

            void Render();

        private:
            glm::vec4 RayGen(const int& i, const int& j);
            HitData TraceRay(const Ray& ray);
            HitData ClosestHit(const Ray& ray);
            HitData Miss(const Ray& ray);

        private:
            Camera m_camera;
            Scene m_scene;
    };
}

#endif // RENDERER_H_
