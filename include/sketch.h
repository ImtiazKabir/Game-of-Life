#ifndef LIB_MEOW_SKETCH_H
#define LIB_MEOW_SKETCH_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#define TITLE_OF_WINDOW "TITLE OF WINDOW"
#define WIDTH (int)500
#define HEIGHT (int)500
#define FPS (uint32_t)60

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
void setup(void);
void clean_up(void);

/* loop.c */
void update(void);
void draw(SDL_Renderer * renderer);

#endif /* LIB_MEOW_SKETCH_H */
