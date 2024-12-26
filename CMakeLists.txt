cmake_minimum_required(VERSION 3.31)

# Project Name and Version
project(Rye CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(RyeApp)

# Link Libraries
target_link_libraries(RyeApp PRIVATE )
