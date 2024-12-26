#!/usr/bin/env sh

glslc RyeApp/Shaders/shader.vert -o build/shaders/vert.spv
glslc RyeApp/Shaders/shader.frag -o build/shaders/frag.spv
