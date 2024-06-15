project "Rye"
    kind "StaticLib"
    language "c++"

    files {
        "src/**.cpp",
    }

    includedirs {
        "include/",

        "../Barley/lib/imgui/",

        "/lib/tracy/public/",
        "/lib/glm/",
    }


    links {
        -- "Tracy",
        ":libpthread.a",
        ":libdl.a",
        "tbb",
    }

    targetdir ("../build/%{cfg.buildcfg}/tmp-%{prj.name}")
    objdir ("../build/%{cfg.buildcfg}/tmp-%{prj.name}")
