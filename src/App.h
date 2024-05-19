#ifndef APP_H_
#define APP_H_

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Image.h"
#include "Camera.h"

#define GL_GLEXT_PROTOTYPES

#include "GLFW/glfw3.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <cmath>
#include <cstdio>
#include <cstdint>
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
        bool show_demo_window = false;
        ImVec4 clear_color = ImVec4(0.07f, 0.13f, 0.17f, 1.0f);

        Image* image = new Image();
        Camera cam;
        int viewport_width, viewport_height;

        Scene my_scene;

};



#endif // APP_H_
