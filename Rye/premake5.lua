project "Rye"
    kind "StaticLib"
    language "c++"

    files {
        "src/**.cpp",
    }

    removefiles {
        "src/Materials/*.cpp"
    }

    includedirs {
        "include/",

        "%{vendor}/imgui/",

        "%{vendor}/tracy/public/",
        "%{vendor}/glm/",
    }
