#ifndef LIB_MEOW_SKETCH_H
#define LIB_MEOW_SKETCH_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#define TITLE_OF_WINDOW "Conway's Game of Life"
#define WIDTH (int)800
#define HEIGHT (int)600
#define FPS (uint32_t)60

#define col (int)80
#define row (int)60

static inline void MEOW_Error(char const * const func_name) {
  fprintf(stderr, "~~IM~~ %s did not work\n"
                  "----------------------\n"
                  "%s", func_name, SDL_GetError());
  SDL_ClearError();
}
char * MEOW_GetPath(char const * const child);  /* lib/getpath.c */


/* event.c */
bool event_handler(void);

/* once.c */
void setup(
  SDL_Renderer * renderer,
  SDL_Texture ** const life,
  SDL_Texture ** const death,
  bool *** const grid
);
void clean_up(
  SDL_Texture * life,
  SDL_Texture * death,
  bool ** grid
);

/* loop.c */
void update(bool ** grid);
void draw(
  SDL_Renderer * renderer,
  SDL_Texture * life,
  SDL_Texture * death,
  bool const * const * const grid
);

#endif /* LIB_MEOW_SKETCH_H */
