cmake_minimum_required(VERSION 3.6)

project(tiny C CXX)

set(CMAKE_C_STANDARD 99)

set(imgui libs/cimgui/imgui)
set(imgui_impl ${imgui}/examples)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_subdirectory(libs/glad)
add_subdirectory(libs/cimgui)

include_directories(${imgui})
include_directories(${GLAD_INCLUDE_DIRS})

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
add_library(imgui_impl STATIC ${imgui_impl}/imgui_impl_opengl3.cpp ${imgui_impl}/imgui_impl_glfw.cpp)
target_compile_definitions(imgui_impl PUBLIC IMGUI_IMPL_API=extern\t\"C\"\t)
target_link_libraries(imgui_impl glad)

add_executable(tiny src/main.c)
target_link_libraries(tiny glad OpenGL::GL glfw m dl cimgui imgui_impl)