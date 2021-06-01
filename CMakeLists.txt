set(OPT_FLAGS, "-Ofast")
set(WARNING_FLAGS, "-Wall -Wextra")

set(
    SRC_OPENGL
    src/shader/shader.cc
    src/init/init.cc
    src/window/window.cc
    src/window/window_cb.cc
    src/camera/camera.cc
    src/object/object.cc
    src/init/init_obj.cc
    src/texture/texture.cc
)

include_directories(
    src
    src/window
    src/tools
    src/object
    src/init
    src/camera
    src/shader
    src/image
    src/texture
)

cmake_minimum_required(VERSION 3.12)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OPT_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_executable(opengl)
target_sources(opengl PRIVATE "src/main.cc" ${SRC_OPENGL})

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(opengl GL GLEW glfw)
