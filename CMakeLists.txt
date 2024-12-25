cmake_minimum_required(VERSION 3.31)

# Project Name and Version
project(RyeTracer C CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# Source files
file(GLOB_RECURSE SOURCES
  src/*.cpp
)

file(GLOB_RECURSE HEADERS
  src/*.h
)


file(GLOB VENDORS
  vendor/imgui/*.cpp
  vendor/imgui/backends/imgui_impl_glfw.cpp
  vendor/imgui/backends/imgui_impl_opengl3.cpp

  vendor/glad/src/glad.c
)

# Add executable
add_executable(RyeTracer ${SOURCES} ${HEADERS} ${VENDORS})

# Vendor Libraries
add_subdirectory(vendor/glfw)

# Link Libraries
target_link_libraries(RyeTracer PRIVATE
  glfw

  pthread
  dl
  tbb
)


# Include directories for the target
target_include_directories(RyeTracer PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
)


# Output directories
set_target_properties(RyeTracer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
