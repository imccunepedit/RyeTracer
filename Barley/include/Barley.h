#ifndef BARLEY_H
#define BARLEY_H

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include "imgui.h"



class App {
    public:
        App();
        virtual ~App();

        void Run();

    public:
        GLFWwindow* window_handle;
    private:
        virtual void Update() {};
        virtual void app_menu() {};

        bool show_demo_window = false;
        bool should_quit = false;
        ImVec4 clear_color = ImVec4(0.07f, 0.13f, 0.17f, 1.0f);

};



#endif // BARLEY_H
