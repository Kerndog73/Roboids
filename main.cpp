#include <iostream>
#include <SDL/SDL.h>
#include <GLES3/gl32.h>
#include <emscripten.h>
#include <Simpleton/OpenGL/buffer.hpp>
#include <Simpleton/OpenGL/vertex array.hpp>
#include <Simpleton/OpenGL/attrib pointer.hpp>
#include <Simpleton/OpenGL/shader program.hpp>

SDL_Renderer *renderer = nullptr;

GL::ArrayBuffer vertBuf;
GL::ElementBuffer elemBuf = {};
GL::VertexArray vertexArray;

extern "C" EMSCRIPTEN_KEEPALIVE void mainloop() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    std::cout << "Got event\n";
    if (e.type == SDL_MOUSEBUTTONDOWN) {
      std::cout << "Received mouse event. Canceling main loop\n";
      emscripten_cancel_main_loop();
    }
  }
  
  glDrawElements(GL_TRIANGLES, 6, GL::TypeEnum<uint16_t>::type, nullptr);
  
  SDL_RenderPresent(renderer);
}

extern "C" int main() {
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    std::cout << "SDL init error: " << SDL_GetError() << '\n';
  }
  
  emscripten_set_main_loop(&mainloop, 0, 0);
  
  SDL_Window *window = SDL_CreateWindow("Window", 0, 0, 400, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (window == nullptr) {
    std::cout << "SDL window create error: " << SDL_GetError() << '\n';
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    std::cout << "SDL renderer create error: " << SDL_GetError() << '\n';
  }
  
  const char VERT_SHADER[] =
R"(#version 300 es

layout (location = 0) in vec2 pos;

out vec2 fragPos;

void main() {
  fragPos = pos;
  gl_Position = vec4(pos, 0.0, 1.0);
})";
  
  const char FRAG_SHADER[] =
R"(#version 300 es

precision mediump float;

in vec2 fragPos;

out vec4 outColor;

void main() {
  outColor = vec4(1.0, 0.0, 0.0, 1.0);
})";
  
  GL::VertShader vert = GL::makeVertShader(VERT_SHADER, sizeof(VERT_SHADER) - 1);
  GL::FragShader frag = GL::makeFragShader(FRAG_SHADER, sizeof(FRAG_SHADER) - 1);
  GL::ShaderProgram prog = GL::makeShaderProgram(vert, frag);
  prog.use();
  
  vertexArray = GL::makeVertexArray();
  vertexArray.bind();
  
  const float verts[] = {
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.5f, 0.5f,
    -0.5f, 0.5f
  };
  const uint16_t elems[] = {
    0, 1, 2,
    2, 3, 0
  };
  
  vertBuf = GL::makeArrayBuffer(verts, sizeof(verts), GL_STATIC_DRAW);
  elemBuf = GL::makeElementBuffer(elems, sizeof(elems), GL_STATIC_DRAW);
  
  GL::attribs<std::tuple<glm::vec2>>();
  
  emscripten_cancel_main_loop();
  emscripten_set_main_loop(&mainloop, 0, 1);
  
  return 0;
}