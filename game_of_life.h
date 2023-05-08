#include "sparse_grid.h"

typedef struct GameOfLife {
    SparseGrid *grid;
    int width;
    int height;
} GameOfLife;

GameOfLife *game_of_life_create();
void game_of_life_destroy(GameOfLife *game);
void game_of_life_toggle_cell_state(GameOfLife *game, int x, int y);
void game_of_life_update(GameOfLife *game);