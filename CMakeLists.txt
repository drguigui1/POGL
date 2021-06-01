set(OPT_FLAGS, "-Ofast")
set(WARNING_FLAGS, "-Wall -Wextra")

set(
    SRC_OPENGL
    src/shader.cc
    src/init.cc
    src/window/window.cc
    src/window/window_cb.cc
    src/camera.cc
    src/object/object.cc
    src/init_obj.cc
)

include_directories(
    src
    src/window
    src/tools
    src/object
)

cmake_minimum_required(VERSION 3.12)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LIB_FLAGS} ${WARNING_FLAGS} -lglfw -lGL -lGLEW")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OPT_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_executable(opengl)
target_sources(opengl PRIVATE "src/main.cc" ${SRC_OPENGL})
