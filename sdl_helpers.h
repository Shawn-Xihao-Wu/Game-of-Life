#ifndef SDL_HELPERS_H
#define SDL_HELPERS_H

#include "sparse_grid.h"
#include <SDL2/SDL.h>

int quit;
int pause;

SDL_mutex *mx;
SDL_cond *cond;

void sdl_init();
void sdl_quit();
void sdl_render_grid(SparseGrid *grid);
void sdl_handle_events(SparseGrid *grid);

#endif /* SDL_HELPERS_H */