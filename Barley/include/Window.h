#ifndef APP_H
#define APP_H

#include <vulkan/vulkan.h>
// include "imgui.h"

class GLFWwindow;

namespace Barley {
    class Window {
        public:
            void Run();


        protected:
            Window();
            virtual ~Window();

            virtual void Update() {};
            virtual void AppMenu() {};

        private:
            void createInstance();

        private:
            GLFWwindow* m_windowHandle;
            VkInstance m_instance;

        //     bool showDemoWindow = false;
            bool shouldQuit = false;
            // ImVec4 clearColor = ImVec4(0.07f, 0.13f, 0.17f, 1.0f);

    };
}


#endif // APP_H
