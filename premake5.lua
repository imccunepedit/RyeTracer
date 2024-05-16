workspace "Renderer"
    configurations "Debug"

project "Renderer"
    kind "consoleapp"
    language "c++"

    files { "src/*.cpp", "lib/imgui/*.cpp", "lib/imgui/backends/imgui_impl_glfw.cpp", "lib/imgui/backends/imgui_impl_opengl3.cpp" }

    includedirs {"lib/imgui/", "include/"}

    links { "GL", "glfw" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "on"
