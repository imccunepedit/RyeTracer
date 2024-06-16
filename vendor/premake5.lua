project "Glad"
    kind "StaticLib"
    language "c"

    files {
        "glad/src/glad.c"
    }

    includedirs {
        "glad/include"
    }

project "ImGui"
    kind "StaticLib"
    language "c++"

    files {
        "imgui/*.cpp",
        "imgui/backends/imgui_impl_glfw.cpp",
        "imgui/backends/imgui_impl_opengl3.cpp"
    }

    includedirs {
        "imgui"
    }
