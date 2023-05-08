#include "sparse_grid.h"
#include "sdl_helpers.h"
#include <unistd.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {

    SparseGrid *grid = sparse_grid_create();

    sparse_grid_add_cell(grid, 25, 25);
    sparse_grid_add_cell(grid, 25, 24);
    sparse_grid_add_cell(grid, 26, 24);
    sparse_grid_add_cell(grid, 27, 24);

    sdl_init();

    int running = 1;
    int paused = 0;

    while (running) {
        sdl_handle_events(grid, &running, &paused);

        if (!paused) {
            sparse_grid_update(grid);
        } else {
            SDL_LockMutex(pause_mx);
            while(paused) {
                SDL_CondWait(pause_cond, pause_mx);
            }
            SDL_UnlockMutex(pause_mx); 
        }

        sdl_render_grid(grid);

        usleep(1000000);
    }

    sdl_quit();

    sparse_grid_destroy(grid);

    return 0;
}