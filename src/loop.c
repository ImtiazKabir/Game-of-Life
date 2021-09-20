#include <SDL2/SDL.h>
#include "sketch.h"

void draw(SDL_Renderer * renderer) {
  if (SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255) == -1) {
    MEOW_Error("Setting the background color with SDL_SetRenderDrawColor");
  }
  if (SDL_RenderClear(renderer) == -1) {
    MEOW_Error("Clearing the window for background with SDL_RenderClear");
  }
}


void update(void) {}
