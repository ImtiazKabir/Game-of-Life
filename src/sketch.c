#include <SDL2/SDL.h>
#include <stdbool.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "sketch.h"

typedef struct MainLoopParam {
  SDL_Renderer * renderer;
  SDL_Texture * life;
  SDL_Texture * death;
  bool ** grid;
  bool quit_flag;
} MainLoopParam_t;

void main_loop(void *v_param);


void MEOW_Repeat(SDL_Renderer *renderer) {
  /* Definition and setting variables for sketch */
  SDL_Texture * life;
  SDL_Texture * death;
  bool ** grid;
  setup(renderer, &life, &death, &grid);


  MainLoopParam_t param = {
    .renderer = renderer,
    .quit_flag = false,
    .life = life,
    .death = death,
    .grid = grid
  };

  #ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(main_loop, &param, 0, 1);
  #else
  while (!param.quit_flag) {
    main_loop(&param);
  }
  #endif

  /* cleaning up sekcth "things" */
  clean_up(life, death, grid);
}


void main_loop(void *v_param) {
  MainLoopParam_t * param = (MainLoopParam_t *) v_param;

  /* handle event */
  if (event_handler()) {
    #ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
    #else
    param->quit_flag = true;
    return;
    #endif /* __EMSCRIPTEN__ */
  }

  /* update and draw */

  SDL_Renderer * renderer = param->renderer;
  SDL_Texture * life = param->life;
  SDL_Texture * death = param->death;
  bool ** grid = param->grid;

  draw(renderer, life, death, (bool const * const * const) grid);
  SDL_Delay(1000 / FPS);
  SDL_RenderPresent(renderer);

  update(grid);
}


