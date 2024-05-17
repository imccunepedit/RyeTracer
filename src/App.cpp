#include "App.h"
#include "imgui.h"


void App::Update() {
    ImGui::Begin("imgui window");
    ImGui::Text("some text");
    ImGui::Checkbox("draw triangle", &drawTriangle);
    ImGui::End();
}


void App::Run() {
    // array of floats that define a triangle, each vertex has three positions and
    // there are three vertexes in a triangle so we have nine floats
    GLfloat vertices[] = {
    -0.5f,-0.5f*float(std::sqrt(3)) / 3, 0.0f,
    0.5f,-0.5f*float(std::sqrt(3))/3, 0.0f,
    0.0f,0.5f*float(std::sqrt(3))/3,0.0f,
    };

    // must be done in this order, we only have one object so we only need one vertex array object and one vertex buffer object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // tell opengl what the current vertex array object to use
    glBindVertexArray(VAO);

    // tell opengl to use our vbo and tell it that it is an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // pass our vertices into the bufferr
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // tell opengl how to interpret our vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // enable our vertex attribute so opengl can use it
    glEnableVertexAttribArray(0);

    // unbind vbo and vao so we don't accidently edit them.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window)) {
        // tell glfw to look for events
        glfwPollEvents();

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        Update();


        // tell opengl what color to make the rendered buffer
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        // tell opengl what shader program to use
        glUseProgram(shaderProgram);
        // bind the vao so opengl can use it
        glBindVertexArray(VAO);
        // draw a triangle using opengls triangle primitive
        if (drawTriangle)
            glDrawArrays(GL_TRIANGLES, 0, 3);

        ImGui::Render();
        // int display_w, display_h;
        // glfwGetFramebufferSize(window, &display_w, &display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // swap the currently displayed buffer with the one that was just rendered
        glfwSwapBuffers(window);

    }

}

App::App() {

    // initiallize glfw and check
    if (!glfwInit())
        std::exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // create a window size x,y,title,fullscreen
    window = glfwCreateWindow(800, 800, "m_floating Hello windows", nullptr, nullptr);

    // make sure window exists
    if (window == nullptr)
        std::exit(1);


    // tell glfw that we want to use our window
    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    // make an opengl viewport
    glViewport(0, 0, 800, 800);


    // create and compile a vertex shader program from our vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // attache the shader to our vertex shader objects
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    // compile our vertex shader object
    glCompileShader(vertexShader);


    // same as vertex shader but for fragment shader, does the coloring of our fragment
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // create a shader program
    shaderProgram = glCreateProgram();
    // attach vertex and fragment shaders to our shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // now that the shaders are attached to the program we can delete the shader objects
    // that were compiled
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


App::~App() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // delete opengl objects we have created that we don't need anymore
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // tell glfw to kill our window and kill its self
    glfwDestroyWindow(window);
    glfwTerminate();
}
