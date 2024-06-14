workspace "BarleyTracing"
    configurations { "debug",
                     "tracy",
                     "release"}

    filter "configurations:debug"
        symbols "Full"

    filter "configurations:release"
        optimize "speed"

    filter "configurations:tracy"
        defines { "TRACY_ENABLE", "TRACY_ON_DEMAND" }
        optimize "speed"


include "Barley"
include "RyeTracer"

require "premake-ecc/ecc"
