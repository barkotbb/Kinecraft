cmake_minimum_required(VERSION 3.12)

# Define the project name
project(Kinecraft1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Add the include directories for GLFW and GLAD
include_directories(${CMAKE_SOURCE_DIR}/GLFW/include)
include_directories(${CMAKE_SOURCE_DIR}/glad/include)

# Specify the GLFW library directory (change this to where your glfw3.lib is located)
link_directories(${CMAKE_SOURCE_DIR}/GLFW/lib)

# Add the glad source file
add_executable(Kinecraft1 "Kinecraft1.cpp" "Kinecraft1.h" "${CMAKE_SOURCE_DIR}/glad/src/glad.c")

# Link GLFW and OpenGL libraries
target_link_libraries(Kinecraft1 PRIVATE glfw3 opengl32)

# Ensure that the correct version of C++ is used
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Kinecraft1 PROPERTY CXX_STANDARD 20)
endif()
