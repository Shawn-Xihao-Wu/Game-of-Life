#ifndef SPARSE_GRID_H
#define SPARSE_GRID_H

#define LENGTH 50
#define WIDTH 50
#define GRID_SIZE LENGTH*WIDTH

typedef struct Cell {
    unsigned char state;
    unsigned char count;
} Cell;

typedef struct Node {
    unsigned int x;
    unsigned int y;
    Cell cell;
    struct Node *next;
} Node;

typedef struct SparseGrid {
    Node *grid[GRID_SIZE];
} SparseGrid;


SparseGrid *sparse_grid_create();

void sparse_grid_destroy(SparseGrid *grid);

int sparse_grid_add_cell(SparseGrid *grid, unsigned int x, unsigned int y);

int sparse_grid_delete_cell(SparseGrid *grid, unsigned int x, unsigned int y);

Cell *sparse_grid_get_cell(SparseGrid *grid, unsigned int x, unsigned y);

void sparse_grid_update(SparseGrid *grid);

#endif /* SPARSE_GRID_H */