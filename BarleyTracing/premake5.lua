project "BarleyTracing"
    kind "WindowedApp"
    language "c++"

    files {
        "src/**.cpp",
    }

    includedirs {
        "include/",

        "../BarleyGUI/include/",

        "../BarleyGUI/lib/imgui/",

        "/lib/tracy/public/",
    }


    links {
        "BarleyGUI",
        "GL",
        "glfw",

        -- "Tracy",
        ":libpthread.a",
        ":libdl.a",
        "tbb"
    }

    targetdir ("../build/bin/%{cfg.buildcfg}-%{prj.name}")
    objdir ("../build/tmp/%{cfg.buildcfg}-%{prj.name}")
