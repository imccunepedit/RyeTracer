workspace "BarleyTracing"
    configurations { "release",
                     "debug",
                     "tracy"}

    filter "configurations:debug"
        symbols "Full"

    filter "configurations:release"
        buildoptions { "-Os" }
        optimize "speed"

    filter "configurations:tracy"
        defines { "TRACY_ENABLE", "TRACY_ON_DEMAND" }
        optimize "speed"



project "*"
    targetdir ("%{wks.location}/build/%{cfg.buildcfg}-bin/%{prj.name}")
    objdir ("%{wks.location}/build/%{cfg.buildcfg}-tmp/%{prj.name}")


vendor = "%{wks.location}/vendor"


project "Rye"
    kind "WindowedApp"
    language "c++"

    files {
        "src/**.cpp",
    }

    includedirs {
        "include/",

        "%{vendor}/imgui/",

        "%{vendor}/glfw/include/",
        "%{vendor}/glad/include/",

        "%{vendor}/tracy/public/",
        "%{vendor}/glm/",
    }

    links {
        "Glad",
        "glfw",
        "ImGui",

        "pthread",
        "dl",
        "tbb",
    }

include "vendor"


require "premake-ecc/ecc"
