#include <SDL2/SDL.h>
#include "sketch.h"

void draw(
  SDL_Renderer * renderer,
  SDL_Texture * life,
  SDL_Texture * death,
  bool const * const * const grid
) {
  if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) == -1) {
    MEOW_Error("Setting the background color with SDL_SetRenderDrawColor");
  }
  if (SDL_RenderClear(renderer) == -1) {
    MEOW_Error("Clearing the window for background with SDL_RenderClear");
  }

  SDL_Rect cell = {.w = WIDTH/col, .h = HEIGHT/row};
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      SDL_Texture *state = grid[i][j]? life:death;
      cell.x = j * cell.w;
      cell.y = i * cell.h;
      if (SDL_RenderCopy(renderer, state, NULL, &cell) < 0) {
        MEOW_Error("Drawing state with SDL_RenderCopy");
      }
    }
  }
}

int countNeighbor(bool const * const * const grid, int const i, int const j);
bool inFuture(bool const current, int const aliveNeighbor);

void update(bool ** grid) {
  bool future[row][col];
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      int const n = countNeighbor((bool const * const * const)grid, i, j);
      future[i][j] = inFuture(grid[i][j], n);
    }
  }
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      grid[i][j] = future[i][j];
    }
  }
}

bool isValid(int const i, int const j);

int countNeighbor(bool const * const * const grid, int const i, int const j) {
  int count = 0;
  for (int y = -1; y <= 1; ++y) {
    for (int x = -1; x <= 1; ++x) {
      if (x==0 && y==0) {
        continue;
      }
      if (isValid(i+y, j+x) && grid[i+y][j+x] == true) {
        ++count;
      }
    }
  }
  return count;
}

bool inFuture(bool const current, int const aliveNeighbor) {
  if (current == true) {
    if (aliveNeighbor==2 || aliveNeighbor==3) {
      return true;
    }
    return false;
  }
  if (aliveNeighbor==3) {
    return true;
  }
  return false;
}

bool isValid(int const i, int const j) {
  if (i < 0 || i >= row) return false;
  if (j < 0 || j >= col) return false;
  return true;
}
