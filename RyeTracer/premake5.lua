project "RyeTracer"
    kind "WindowedApp"
    language "c++"

    files {
        "src/**.cpp",
    }

    includedirs {
        "include/",

        "../Barley/include/",

        "../Barley/lib/imgui/",

        "/lib/tracy/public/",
    }


    links {
        "Barley",
        "GL",
        "glfw",

        -- "Tracy",
        ":libpthread.a",
        ":libdl.a",
        "tbb"
    }

    targetdir ("../build/bin/%{cfg.buildcfg}-%{prj.name}")
    objdir ("../build/tmp/%{cfg.buildcfg}-%{prj.name}")
