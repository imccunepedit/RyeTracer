workspace "Renderer"
    configurations { "debug", "tracy" }

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "Full"

    filter "configurations:tracy"
        defines { "TRACY_ENABLE", "TRACY_ON_DEMAND" }
        optimize "speed"


project "ImGui"
    kind "StaticLib"
    language "c++"
    toolset "clang"

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
        "src/**.cpp",
        "src/**.h",
        "lib/tracy/public/TracyClient.cpp",
        "lib/tracy/public/tracy/Tracy.hpp"
    }

    includedirs {
        "lib/imgui/",
        "lib/",
        "lib/tracy/public/"
    }


    links {
        "GL",
        "glfw",
        "ImGui",
        ":libpthread.a",
        ":libdl.a",
        "tbb"
    }


require "premake-ecc/ecc"
