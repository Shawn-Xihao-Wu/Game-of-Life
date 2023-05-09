#include "sparse_grid.h"
#include "sdl_helpers.h"
#include <SDL2/SDL.h>

SparseGrid *grid;

void gilder_gun(SparseGrid *grid) {
    sparse_grid_add_cell(grid, 3, 6);
    sparse_grid_add_cell(grid, 4, 6);
    sparse_grid_add_cell(grid, 3, 7);
    sparse_grid_add_cell(grid, 4, 7);

    sparse_grid_add_cell(grid, 13, 6);
    sparse_grid_add_cell(grid, 13, 7);
    sparse_grid_add_cell(grid, 13, 8);
    sparse_grid_add_cell(grid, 14, 5);
    sparse_grid_add_cell(grid, 14, 9);
    sparse_grid_add_cell(grid, 15, 4);
    sparse_grid_add_cell(grid, 15, 10);
    sparse_grid_add_cell(grid, 16, 4);
    sparse_grid_add_cell(grid, 16, 10);
    sparse_grid_add_cell(grid, 17, 7);
    sparse_grid_add_cell(grid, 18, 5);
    sparse_grid_add_cell(grid, 18, 9);
    sparse_grid_add_cell(grid, 19, 6);
    sparse_grid_add_cell(grid, 19, 7);
    sparse_grid_add_cell(grid, 19, 8);
    sparse_grid_add_cell(grid, 20, 7);

    sparse_grid_add_cell(grid, 23, 4);
    sparse_grid_add_cell(grid, 23, 5);
    sparse_grid_add_cell(grid, 23, 6);

    sparse_grid_add_cell(grid, 24, 4);
    sparse_grid_add_cell(grid, 24, 5);
    sparse_grid_add_cell(grid, 24, 6);

    sparse_grid_add_cell(grid, 25, 3);
    sparse_grid_add_cell(grid, 25, 7);

    sparse_grid_add_cell(grid, 27, 2);
    sparse_grid_add_cell(grid, 27, 3);
    sparse_grid_add_cell(grid, 27, 7);
    sparse_grid_add_cell(grid, 27, 8);

    sparse_grid_add_cell(grid, 37, 4);
    sparse_grid_add_cell(grid, 37, 5);
    sparse_grid_add_cell(grid, 38, 4);
    sparse_grid_add_cell(grid, 38, 5);
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s [plain|gliders]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "plain") == 0) {
        grid = sparse_grid_create();
    } else if (strcmp(argv[1], "gliders") == 0) {
        grid = sparse_grid_create();
        gilder_gun(grid);
    } else {
        printf("Invalid argument name: %s\n", argv[1]);
        return 1;
    }

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