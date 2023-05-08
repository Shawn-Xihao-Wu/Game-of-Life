#include "sparse_grid.h"
#include <stdio.h>
#include <unistd.h> // for usleep

int main(int argc, char *argv[]) {

    SparseGrid *grid = sparse_grid_create();

    sparse_grid_add_cell(grid, 25, 25);
    sparse_grid_add_cell(grid, 25, 24);
    sparse_grid_add_cell(grid, 26, 24);
    sparse_grid_add_cell(grid, 27, 24);

    for (int i = 0; i < 10; i ++) {
        //render
        for (unsigned int x = 0; x < LENGTH; x++) {
            for (unsigned int y = 0; y < WIDTH; y++) {
                Cell *cell = sparse_grid_get_cell(grid, x, y);

                if (cell) {
                    printf("x");
                } else {
                    printf(" ");
                }
            }

            printf("\n");
        }

        usleep(100000);

        sparse_grid_update(grid);
    }

    return 0;
}