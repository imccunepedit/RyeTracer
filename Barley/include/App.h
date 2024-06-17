#ifndef APP_H_
#define APP_H_

#include "Window.h"

// #include <future>
// #include <vector>

// #include "Image.h"

// #include "Camera.h"
// #include "Scene.h"
// #include "Renderer.h"

// using namespace Rye;

namespace Barley {
    class App : public Window
    {
        public:
            App();
            ~App();

        private:
            void Update() override;
            void AppMenu() override;

        // private:
        //     bool m_renderEveryFrame = false;
        //     bool m_showCameraDebug = false;
        //     bool m_rendering = false;

        //     int m_lastRenderMS;

        //     std::future<int> renderThread = std::async([] { return 0; });

        //     Scene m_scene;
        //     Camera m_camera;
        //     Renderer m_renderer = Renderer(&m_camera, &m_scene);

        //     Barley::Image Viewport;

    };
}

#endif /* APP_H_ */
