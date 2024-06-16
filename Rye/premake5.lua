project "Rye"
    kind "StaticLib"
    language "c++"

    files {
        "src/**.cpp",
    }

    includedirs {
        "include/",

        "%{vendor}/imgui/",

        "%{vendor}/tracy/public/",
        "%{vendor}/glm/",
        "%{vendor}/glad/include",
    }
