cmake_minimum_required(VERSION 3.14)
project(kevin LANGUAGES C VERSION 0.0)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/lib/cmake-git/)
include(Dependency)

set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)
set(DEPS_DIR ${PROJECT_SOURCE_DIR}/lib)

find_package(Threads REQUIRED)

git(GLFW https://github.com/glfw/glfw 8d3595fb4d4d919e27e1a755095ae1ffae5f50be)

cache(GLFW_BUILD_EXAMPLES OFF BOOL)
cache(GLFW_BUILD_TESTS OFF BOOL)
cache(GLFW_BUILD_DOCS OFF BOOL)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

add_executable(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${DEPS_DIR}/stb STATIC)
target_include_directories(${PROJECT_NAME} PUBLIC ${DEPS_DIR}/glad STATIC)

target_sources(${PROJECT_NAME}
  PRIVATE
    lib/glad/glad/src/glad.c
    src/core/renderer/ogl.c
    src/core/renderer/window.c
    src/core/renderer/renderer.c
    src/core/renderer/entity.c
    src/main.c)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    GLFW::GLFW
    Threads::Threads)
