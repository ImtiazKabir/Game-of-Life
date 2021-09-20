#include <SDL2/SDL.h>
#include <stdbool.h>

#include "sketch.h"

bool event_handler(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return true;
    }
  }
  return false;
}
