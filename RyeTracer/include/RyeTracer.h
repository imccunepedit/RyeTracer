#include "App.h"

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
            bool m_renderEveryFrame = true;
            bool m_showCameraDebug = false;

            Scene m_scene;
            Camera m_camera;
            Renderer m_renderer = Renderer(&m_camera, &m_scene);

            Barley::Image Viewport;

    };
}
