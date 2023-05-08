#include "sparse_grid.h"
#include <stdlib.h>
#include <stdio.h>

unsigned int hash(unsigned int x, unsigned int y) {
    return (x * 2141 ^ y * 3313) % GRID_SIZE;
}

SparseGrid *sparse_grid_create() {
    SparseGrid *grid = malloc(sizeof(*grid));
    
    if (grid == NULL) {
        printf("Failed to allocate memory for SparseGrid\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        grid->grid[i] = NULL;
    }

    return grid;
}

void sparse_grid_destroy(SparseGrid *grid) {
    //Free the memory for each node in the grid
    for (int i = 0; i < GRID_SIZE; i++) {
        Node *cur = grid->grid[i];
        while (cur) {
            Node *next = cur->next;
            free(cur);
            cur = next;
        }
    }

    free(grid);
}

int sparse_grid_add_cell(SparseGrid *grid, unsigned int x, unsigned int y) {
    unsigned int index = hash(x, y);
    Node *cur = grid->grid[index];

    //Check if the cell already exists in the grid
    while (cur) {
        if (cur->x == x && cur->y == y) {
            return 0;
        }
        cur = cur->next;
    }

    //Create a new node for the cell
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        printf("Failed to allocate memory for Node\n");
        exit(EXIT_FAILURE);
    }
    node->x = x;
    node->y = y;
    node->cell.state = 1;
    node->cell.count = 0;
    node->next = grid->grid[index];     //Add to the front of the list

    //Add the new node to the grid
    grid->grid[index] = node;

    return 1;
}

Cell *sparse_grid_get_cell(SparseGrid *grid, unsigned int x, unsigned y) {
    unsigned int index = hash(x, y);
    Node *cur = grid->grid[index];

    while (cur) {
        if (cur->x == x && cur->y == y) {
            return &(cur->cell);
        }
        cur = cur->next;
    }

    return NULL;
}

int sparse_grid_delete_cell(SparseGrid *grid, unsigned int x, unsigned int y) {
    unsigned int index = hash(x,y);
    Node *cur = grid->grid[index];
    Node *prev = NULL;

    while (cur) {
        if (cur->x == x && cur->y == y) { 
            //Finding the cell to delete
            if (prev == NULL) { 
                //If the cell is the head of the list
                grid->grid[index] = cur->next;
            } else { 
                //If the cell is in the middle
                prev->next = cur->next;
            }
            free(cur);
            return 1;   //SUCCESS!
        }
        prev = cur;
        cur = cur->next;
    }

    return 0;   //NO SUCH CELL FOUND!
}

int sparse_grid_put_cell_inc_count(SparseGrid *grid, unsigned int x, unsigned int y) {
    
    if (x < 0 || x >= LENGTH || y < 0 || y >= WIDTH) {return 0;}

    unsigned int index = hash(x, y);
    Node *cur = grid->grid[index];

    //if the cell already exists in the grid, just increase the count
    while (cur) {
        if (cur->x == x && cur->y == y) {
            cur->cell.count++;
            return 0;
        }
        cur = cur->next;
    }

    //Create a new node for the cell if not exist
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        printf("Failed to allocate memory for Node\n");
        exit(EXIT_FAILURE);
    }
    node->x = x;
    node->y = y;
    node->cell.state = 0;               //Not alive
    node->cell.count = 1;               //Initialize count
    node->next = grid->grid[index];     //Add to the front of the list

    //Add the new node to the grid
    grid->grid[index] = node;

    return 1;
}

void sparse_grid_update(SparseGrid *grid) {

    //Update the count of all the live cells and their neighboring cells
    unsigned int x = 0;
    unsigned int y = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        Node *cur = grid->grid[i];
        while (cur) {
            if (cur->cell.state == 1) {
                x = cur->x;
                y = cur->y;
                sparse_grid_put_cell_inc_count(grid, x-1, y-1);
                sparse_grid_put_cell_inc_count(grid, x-1, y);
                sparse_grid_put_cell_inc_count(grid, x-1, y+1);
                sparse_grid_put_cell_inc_count(grid, x, y-1);
                sparse_grid_put_cell_inc_count(grid, x, y);
                sparse_grid_put_cell_inc_count(grid, x, y+1);
                sparse_grid_put_cell_inc_count(grid, x+1, y-1);
                sparse_grid_put_cell_inc_count(grid, x+1, y);
                sparse_grid_put_cell_inc_count(grid, x+1, y+1);
            }
            cur = cur->next;
        }
    }

    //Leave only the cells that satisfy the criteria
    for (int i = 0; i < GRID_SIZE; i++) {
        Node *cur = grid->grid[i];
        while (cur) {
            Node *next = cur->next;
            if ((cur->cell.count == 3) || (cur->cell.count == 4 && cur->cell.state == 1)) {
                //KEEP THE CELL
                cur->cell.count = 0;
                cur->cell.state = 1;

            } else {
                sparse_grid_delete_cell(grid, cur->x, cur->y);
            }
            cur = next;
        }
    }
}