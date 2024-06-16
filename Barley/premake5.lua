project "Barley"
    kind "WindowedApp"
    language "c++"

    files {
        "src/**.cpp",
    }

    includedirs {
        "include/",
        "%{wks.location}/Rye/include/",

        "%{vendor}/imgui/",
        "%{vendor}/glfw/include/",
        "%{vendor}/glad/include/",
    }


    links {
        "Glad",
        "glfw",
        "ImGui",
        "Rye",

        "pthread",
        "dl",
        "tbb",
    }
