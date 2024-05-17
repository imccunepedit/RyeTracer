workspace "Renderer"
    configurations "debug"

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "on"



project "ImGui"
    kind "StaticLib"
    language "c++"

    files {
        "lib/imgui/*.cpp",
        "lib/imgui/backends/imgui_impl_glfw.cpp",
        "lib/imgui/backends/imgui_impl_opengl3.cpp"
    }

    includedirs {
        "lib/imgui/"
    }


project "Renderer"
    kind "WindowedApp"
    language "c++"

    files {
        "src/*.cpp",
        "include/*.h"
    }

    includedirs {
        "lib/imgui/",
        "include/"
    }

    links {
        "GL",
        "glfw",
        "ImGui"
    }


require "premake-ecc/ecc"
