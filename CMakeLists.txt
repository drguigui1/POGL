set(OPT_FLAGS, "-Ofast")

set(
    SRC_OPENGL
    src/camera/camera.cc
    src/init/init.cc
    src/init/init_obj.cc
    src/noise/noise.cc
    src/noise/noise2.cc
    src/object/object.cc
    src/shader/shader.cc
    src/texture/texture.cc
    src/material/material.cc
    src/window/window.cc
    src/window/window_cb.cc
    src/image/image.cc
    src/render/render.cc
    src/skybox/skybox.cc
    src/loader/model.cc
    src/loader/mesh.cc
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
    src/material
    src/skybox
    src/noise
    src/render
    src/loader
)

cmake_minimum_required(VERSION 3.12)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OPT_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_executable(opengl)
target_sources(opengl PRIVATE "src/main.cc" ${SRC_OPENGL})

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(ASSIMP REQUIRED)

target_link_libraries(opengl GL GLEW glfw assimp)
target_compile_options(opengl PRIVATE -Wall -Wextra)
