#ifndef APP_H
#define APP_H

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include "imgui.h"


namespace Barley {
    class App {
        public:
            App();
            virtual ~App();

            void Run();

        public:
            GLFWwindow* windowHandle;

        private:
            virtual void Update() {};
            virtual void AppMenu() {};

            bool showDemoWindow = false;
            bool shouldQuit = false;
            ImVec4 clearColor = ImVec4(0.07f, 0.13f, 0.17f, 1.0f);

    };
}


#endif // APP_H
