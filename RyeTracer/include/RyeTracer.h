#include "App.h"

#include <future>

#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Image.h"


namespace Rye {
    class RyeTracer : public Barley::App
    {
        public:
            RyeTracer();
            ~RyeTracer();
        private:
            void Update() override;
            void AppMenu() override;

        private:
            bool m_renderEveryFrame = false;
            bool m_showCameraDebug = false;

            std::future<void> renderThread = std::async([] { return; });

            Scene m_scene;
            Camera m_camera;
            Renderer m_renderer = Renderer(&m_camera, &m_scene);

            Barley::Image Viewport;

    };
}
