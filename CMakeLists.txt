cmake_minimum_required(VERSION 3.10)
project(Roboids)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER /usr/local/Cellar/emscripten/1.37.33/libexec/emcc)

if (CMAKE_BUILD_TYPE MATCHES RELEASE)
  set(EXTRA_FLAGS "-O3 --closure 1")
else()
  set(EXTRA_FLAGS "-s DEMANGLE_SUPPORT=1")
endif()

set(LINKER_FLAGS " \
  ${EXTRA_FLAGS} \
  -s USE_WEBGL2=1 \
  -s USE_SDL=2 \
  --pre-js ${PROJECT_SOURCE_DIR}/Webpage/init.js \
  --shell-file ${PROJECT_SOURCE_DIR}/Webpage/index.html \
")
include_directories(/usr/local/include/)

add_definitions(-DNO_INCLUDE_SDL_OPENGL)

# Sources

set(SOURCE_FILES main.cpp)

# Web ASM

add_executable(WebASM ${SOURCE_FILES})
set_target_properties(WebASM PROPERTIES OUTPUT_NAME index.html)
set_target_properties(WebASM PROPERTIES LINK_FLAGS "${LINKER_FLAGS} -s WASM=1")