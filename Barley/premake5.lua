project "Barley"
    kind "WindowedApp"
    language "c++"

    files {
        "src/**.cpp",

        "lib/imgui/*.cpp",
        "lib/imgui/backends/imgui_impl_glfw.cpp",
        "lib/imgui/backends/imgui_impl_opengl3.cpp"
    }

    includedirs {
        "include/",
        "lib/imgui/",

        "../Rye/include/"
    }


    links {
        "GL",
        "glfw",
        "Rye",

        ":libpthread.a",
        ":libdl.a",
        "tbb",
    }

    targetdir ("../build/%{cfg.buildcfg}/bin-%{prj.name}")
    objdir ("../build/%{cfg.buildcfg}/tmp-%{prj.name}")
