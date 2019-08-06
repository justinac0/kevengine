cmake_minimum_required(VERSION 3.10)
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
target_include_directories(${PROJECT_NAME} PUBLIC ${DEPS_DIR}/cglm STATIC)

set(LUA_SRC
  lib/lua-5.3.5/lapi.c
  lib/lua-5.3.5/lauxlib.c
  lib/lua-5.3.5/lbaselib.c
  lib/lua-5.3.5/lbitlib.c
  lib/lua-5.3.5/lcode.c
  lib/lua-5.3.5/lcorolib.c
  lib/lua-5.3.5/lctype.c
  lib/lua-5.3.5/ldblib.c
  lib/lua-5.3.5/ldebug.c
  lib/lua-5.3.5/ldo.c
  lib/lua-5.3.5/ldump.c
  lib/lua-5.3.5/lfunc.c
  lib/lua-5.3.5/lgc.c
  lib/lua-5.3.5/linit.c
  lib/lua-5.3.5/liolib.c
  lib/lua-5.3.5/llex.c
  lib/lua-5.3.5/lmathlib.c
  lib/lua-5.3.5/lmem.c
  lib/lua-5.3.5/loadlib.c
  lib/lua-5.3.5/lobject.c
  lib/lua-5.3.5/lopcodes.c
  lib/lua-5.3.5/loslib.c
  lib/lua-5.3.5/lparser.c
  lib/lua-5.3.5/lstate.c
  lib/lua-5.3.5/lstring.c
  lib/lua-5.3.5/lstrlib.c
  lib/lua-5.3.5/ltable.c
  lib/lua-5.3.5/ltablib.c
  lib/lua-5.3.5/ltm.c
  # lib/lua-5.3.5/lua.c
  # lib/lua-5.3.5/luac.c
  lib/lua-5.3.5/lundump.c
  lib/lua-5.3.5/lutf8lib.c
  lib/lua-5.3.5/lvm.c
  lib/lua-5.3.5/lzio.c)

target_sources(${PROJECT_NAME}
  PRIVATE
    ${LUA_SRC}
    lib/glad/glad/src/glad.c
    src/core/util/mem.c
    src/core/scene.c
    src/core/renderer/ogl.c
    src/core/renderer/window.c
    src/core/renderer/renderer.c
    src/core/renderer/camera.c
    src/core/renderer/entity.c
    src/main.c)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    GLFW::GLFW
    Threads::Threads)
