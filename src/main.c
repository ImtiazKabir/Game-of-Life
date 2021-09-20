#include <SDL2/SDL.h>
#include "MEOW.h"

int main(void) {
  SDL_Window * window;
  SDL_Renderer * renderer;
  MEOW_Init(&window, &renderer);
  MEOW_Repeat(renderer);
  MEOW_Destroy(window, renderer);
  return 0;
}
