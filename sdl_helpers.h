#ifndef SDL_HELPERS_H
#define SDL_HELPERS_H

#include "sparse_grid.h"
#include <SDL2/SDL.h>

SDL_mutex *pause_mx;
SDL_cond *pause_cond;

void sdl_init();
void sdl_quit();
void sdl_render_grid(SparseGrid *grid);
void sdl_handle_events(SparseGrid *grid, int *running, int *paused);

#endif /* SDL_HELPERS_H */