#include "sparse_grid.h"
#include "sdl_helpers.h"
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {

    SparseGrid *grid = sparse_grid_create();

    sparse_grid_add_cell(grid, 25, 25);
    sparse_grid_add_cell(grid, 25, 24);
    sparse_grid_add_cell(grid, 26, 24);
    sparse_grid_add_cell(grid, 27, 24);
    sparse_grid_add_cell(grid, 27, 25);
    sparse_grid_add_cell(grid, 28, 25);
    sparse_grid_add_cell(grid, 24, 25);
    sparse_grid_add_cell(grid, 24, 27);

    sdl_init();

    sdl_render_grid(grid);

    while (1) {
        sdl_handle_events(grid);

        if (quit) {
            break;
        }

        if (!pause) {
            
            sparse_grid_update(grid);
            sdl_render_grid(grid);
        }

    }
    
    sdl_quit();

    sparse_grid_destroy(grid);

    return 0;
}