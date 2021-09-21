#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "sketch.h"

void createGrid(bool *** grid);
void createTexture(
  SDL_Renderer *renderer,
  SDL_Texture ** const texture,
  char const * const dir
);

void setup(
  SDL_Renderer * renderer,
  SDL_Texture ** const life,
  SDL_Texture ** const death,
  bool *** const grid
) {

  createTexture(renderer, life, "assets/life.png");
  createTexture(renderer, death, "assets/death.png");

  /* create the board */
  srand(time(NULL));
  createGrid(grid);
}

void createGrid(bool *** const grid) {
  *grid = (bool **) calloc(row, sizeof(bool *));
  if (*grid == NULL) {
    MEOW_Error("Allocating memory for grid");
  }
  for (int i = 0; i < row; ++i) {
    (*grid)[i] = (bool *) calloc(col, sizeof(bool));
    if ((*grid)[i] == NULL) {
      MEOW_Error("Allocating memory for rows");
    }
    for (int j = 0; j < col; ++j) {
      (*grid)[i][j] = rand() % 2? true:false;
    }
  }
}

void createTexture(
  SDL_Renderer *renderer,
  SDL_Texture ** const texture,
  char const * const dir
) {

  char * path = MEOW_GetPath(dir);
  SDL_Surface * surface = IMG_Load(path);
  if (surface == NULL) {
    MEOW_Error("Creating surface for life with IMG_Load");
  }
  *texture = SDL_CreateTextureFromSurface(renderer, surface);
  free(path);
  SDL_FreeSurface(surface);
}


void clean_up(
  SDL_Texture * life,
  SDL_Texture * death,
  bool ** grid
) {
  SDL_DestroyTexture(life);
  SDL_DestroyTexture(death);

  for (int i = 0; i < row; ++i) {
    free(grid[i]);
  }
  free(grid);
}

