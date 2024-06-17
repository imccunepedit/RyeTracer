project "ImGui"
    kind "StaticLib"
    language "c++"

    files {
        "imgui/*.cpp",
        "imgui/backends/imgui_impl_glfw.cpp",
        "imgui/backends/imgui_impl_vulkan.cpp"
    }

    includedirs {
        "imgui"
    }
