#define LENGTH 1000
#define WIDTH 1000
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

void sparse_grid_update(SparseGrid *grid);

