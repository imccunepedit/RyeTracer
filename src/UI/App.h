#ifndef APP_H_
#define APP_H_

#include "Window.h"

#include <future>
#include <vector>

#include "UI/Image.h"

#include "Renderer/Camera.h"
#include "Renderer/Scene.h"
#include "Renderer/Renderer.h"

using namespace Rye;

namespace Rye::UI {
    class App : public Window
    {
        public:
            App();
            ~App();
        private:
            void Update() override;
            void AppMenu() override;

        private:
            bool m_renderEveryFrame = true;
            bool m_showCameraDebug = false;
            bool m_rendering = false;

            int m_lastRenderMS;

            std::future<int> renderThread = std::async([] { return 0; });

            Scene m_scene;
            Camera m_camera;
            Renderer m_renderer = Renderer(&m_camera, &m_scene);

            Image Viewport;

    };
}

#endif /* APP_H_ */
