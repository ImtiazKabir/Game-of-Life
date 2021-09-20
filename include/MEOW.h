#ifndef LIB_MEOW_H
#define LIB_MEOW_H

#include <SDL2/SDL.h>

void MEOW_Init(SDL_Window **window, SDL_Renderer **renderer);
void MEOW_Repeat(SDL_Renderer *renderer); /* sketch.c */
void MEOW_Destroy(SDL_Window *window, SDL_Renderer *renderer);

#endif /* LIB_MEOW_H */
