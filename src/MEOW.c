#include "MEOW.h"
#include "sketch.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

void MEOW_Init(SDL_Window ** window, SDL_Renderer ** renderer) {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

  *window = SDL_CreateWindow(
    TITLE_OF_WINDOW,
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WIDTH, HEIGHT,
    SDL_WINDOW_SHOWN);
  if (!*window) {
    MEOW_Error("Creating the window with SDL_CreateWindow");
  }

  *renderer = SDL_CreateRenderer(
    *window, -1, SDL_RENDERER_PRESENTVSYNC);
  if (!*renderer) {
    MEOW_Error("Creating the renderer with SDL_CreateRenderer");
  }
}

void MEOW_Destroy(SDL_Window * window, SDL_Renderer * renderer) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}

