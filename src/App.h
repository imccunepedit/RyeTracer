#ifndef APP_H_
#define APP_H_

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <cstdint>

#define GL_GLEXT_PROTOTYPES

#include "GLFW/glfw3.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <cmath>
#include <cstdio>
#include <stdlib.h>
#include <iostream>

class App {
    public:

        App();
        ~App();

        void Run();
        void Update();


    private:
        GLFWwindow* window;
        bool show_demo_window = true;
        ImVec4 clear_color = ImVec4(0.07f, 0.13f, 0.17f, 1.0f);
        int image_width = 255;
        int image_height = 300;
        GLuint image_texture;

};



#endif // APP_H_
