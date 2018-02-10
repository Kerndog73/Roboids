#include <iostream>
#include <SDL/SDL.h>
#include <emscripten.h>

extern "C" EMSCRIPTEN_KEEPALIVE void mainloop() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    std::cout << "Got event\n";
    if (e.type == SDL_MOUSEBUTTONDOWN) {
      emscripten_cancel_main_loop();
    }
  }
}

extern "C" int main() {
  static_assert(*__PRETTY_FUNCTION__ == 'i');
  
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    std::cout << "SDL Error: " << SDL_GetError() << '\n';
  }
  
  std::cout << "Starting mainloop\n";
  
  emscripten_set_main_loop(&mainloop, 0, true);
  
  std::cout << "Finishing main loop\n";
  
  SDL_Quit();
  
  return 0;
}