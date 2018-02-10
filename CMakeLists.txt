cmake_minimum_required(VERSION 3.10)
project(Roboids)

set(CMAKE_CXX_STANDARD 17)
set(EMSCRIPTEN /usr/local/Cellar/emscripten/1.37.33/libexec/emcc)
set(CMAKE_EXE_LINKER_FLAGS -s USE_WEBGL2=1 -s USE_SDL=2)
include_directories(/usr/local/include/)

# Sources

set(SOURCE_FILES main.cpp)

# Native

# add_executable(Native ${SOURCE_FILES})
# set_target_properties(Native PROPERTIES OUTPUT_NAME Native/main)

# Web JS

set(CMAKE_CXX_COMPILER ${EMSCRIPTEN})
add_executable(WebJS ${SOURCE_FILES})
set_target_properties(WebJS PROPERTIES OUTPUT_NAME WebJS/index.html)

# Web ASM

set(CMAKE_CXX_COMPILER ${EMSCRIPTEN})
add_executable(WebASM ${SOURCE_FILES})
set_target_properties(WebASM PROPERTIES OUTPUT_NAME WebASM/index.html)
set_target_properties(WebASM PROPERTIES LINK_FLAGS "-s WASM=1")