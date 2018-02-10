cmake_minimum_required(VERSION 3.10)
project(Roboids)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER /usr/local/Cellar/emscripten/1.37.33/libexec/emcc)
set(LINKER_FLAGS " \
  -s USE_WEBGL2=1 \
  -s USE_SDL=2 \
  --closure 1 \
  --pre-js ${PROJECT_SOURCE_DIR}/Webpage/init.js \
  --shell-file ${PROJECT_SOURCE_DIR}/Webpage/index.html \
")
include_directories(/usr/local/include/)
add_definitions(-DINCLUDE_OPENGL_ES2_HEADERS)

# Sources

set(SOURCE_FILES main.cpp)

# Web JS

add_executable(WebJS ${SOURCE_FILES})
set_target_properties(WebJS PROPERTIES OUTPUT_NAME WebJS/index.html)
set_target_properties(WebJS PROPERTIES LINK_FLAGS ${LINKER_FLAGS})

# Web ASM

add_executable(WebASM ${SOURCE_FILES})
set_target_properties(WebASM PROPERTIES OUTPUT_NAME WebASM/index.html)
set_target_properties(WebASM PROPERTIES LINK_FLAGS "${LINKER_FLAGS} -s WASM=1")