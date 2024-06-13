#include "App.h"

#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Image.h"

namespace Barley {

    class BarleyTracer : public App
    {
        public:
            BarleyTracer();
            ~BarleyTracer();
        private:
            void Update() override;
            void AppMenu() override;

        private:
            bool m_renderEveryFrame = true;
            bool m_showCameraDebug = false;

            Scene m_scene;
            Camera m_camera;
            Renderer m_renderer = Renderer(m_camera, m_scene);

            // int viewport_width, viewport_height;
    };
}
