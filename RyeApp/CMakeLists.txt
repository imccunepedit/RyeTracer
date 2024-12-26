cmake_minimum_required(VERSION 3.31)

# Project Name and Version
project(RyeApp CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(vendor_dir ../vendor/)

# Source files
file(GLOB_RECURSE sources
  src/*.cpp
)

file(GLOB_RECURSE headers
  src/*.h
)

FILE(GLOB vendors
  ${vendor_dir}/imgui/*.cpp
  ${vendor_dir}/imgui/backends/imgui_impl_glfw.cpp
  ${vendor_dir}/imgui/backends/imgui_impl_vulkan.cpp
)

# Add executable
add_executable(RyeApp ${sources} ${headers} ${vendors})


# Vendor Libraries
find_package(glfw3 3.4 REQUIRED)
find_package(Vulkan REQUIRED)

# Link Libraries
target_link_libraries(RyeApp PRIVATE
  glfw
  Vulkan::Vulkan

  # pthread
  # dl
  # tbb
)


# Include directories for the target
target_include_directories(RyeApp PRIVATE
  ${vendor_dir}/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)


# Output directories
set_target_properties(RyeApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
