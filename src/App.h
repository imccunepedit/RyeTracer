#ifndef APP_H_
#define APP_H_

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include "imgui.h"



class App {
    public:
        App();
        virtual ~App();

        void Run();

    private:
        virtual void Update() {};

        GLFWwindow* window;
        bool show_demo_window = false;
        bool should_quit = false;
        ImVec4 clear_color = ImVec4(0.07f, 0.13f, 0.17f, 1.0f);

};



#endif // APP_H_
