project "Barley"
    kind "StaticLib"
    language "c++"

    files {
        "src/**.cpp",

        "lib/imgui/*.cpp",
        "lib/imgui/backends/imgui_impl_glfw.cpp",
        "lib/imgui/backends/imgui_impl_opengl3.cpp"
    }

    includedirs {
        "include/",
        "lib/imgui/"
    }


    links {
        "GL",
        "glfw",
        "ImGui",
    }

    targetdir ("../build/bin/%{cfg.buildcfg}-%{prj.name}")
    objdir ("../build/tmp/%{cfg.buildcfg}-%{prj.name}")
