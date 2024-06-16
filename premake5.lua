workspace "BarleyTracing"
    configurations { "debug",
                     "tracy",
                     "release"}

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

include "vendor"
include "Barley"
include "Rye"


require "premake-ecc/ecc"
