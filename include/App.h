#ifndef APP_H_
#define APP_H_

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

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
        GLuint VAO, VBO, shaderProgram;
        bool drawTriangle = true;


        // vertex shader
        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

        //Fragment Shader source code
        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
            "}\n\0";

};




#endif // APP_H_
