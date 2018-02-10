#include <iostream>
#include <SDL/SDL.h>
#include <GLES3/gl3.h>
#include <emscripten.h>

SDL_Renderer *renderer = nullptr;

extern "C" EMSCRIPTEN_KEEPALIVE void mainloop() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    std::cout << "Got event\n";
    if (e.type == SDL_MOUSEBUTTONDOWN) {
      emscripten_cancel_main_loop();
    }
  }
  
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
  
  GLuint buf;
  glGenBuffers(1, &buf);
  glBindBuffer(GL_ARRAY_BUFFER, buf);
  
  emscripten_cancel_main_loop();
  emscripten_set_main_loop(&mainloop, 0, 1);
  
  return 0;
}