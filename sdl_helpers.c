#include "sdl_helpers.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 1000
#define WINDOW_LENGTH 1000
#define CELL_SIZE 20

#define GAME_UPDATE_INTERVAL 1000 / 3

SDL_Window *window;
SDL_Renderer *renderer;


void sdl_init() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    //Create the window
    window = SDL_CreateWindow("Game of Life",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                WINDOW_WIDTH,
                                WINDOW_LENGTH,
                                SDL_WINDOW_SHOWN);
    
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    //Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    quit = 0;
    pause = 0;

    // mx = SDL_CreateMutex();
    // cond = SDL_CreateCond(); 
}

void sdl_quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    // SDL_DestroyCond(cond);
    // SDL_DestroyMutex(mx);

    SDL_Quit();
}


void sdl_render_grid(SparseGrid *grid) {
    //Clear the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    //Set the draw color for cells
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //Iterate over the live cells in the grid
    for (unsigned int i = 0; i < GRID_SIZE; i++) {
        Node *cur = grid->grid[i];
        while (cur) {
            
            SDL_Rect rect;
            rect.x = cur->x * CELL_SIZE;
            rect.y = cur->y * CELL_SIZE;
            rect.w = CELL_SIZE;
            rect.h = CELL_SIZE;

            SDL_RenderFillRect(renderer, &rect);
            

            cur = cur->next;
        }
    }

    // Set the draw color for gridlines
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

    // Draw horizontal gridlines
    for (int i = 0; i <= WINDOW_WIDTH / CELL_SIZE; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, WINDOW_WIDTH, i * CELL_SIZE);
    }

    // Draw vertical gridlines
    for (int i = 0; i <= WINDOW_LENGTH / CELL_SIZE; ++i) {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, WINDOW_LENGTH);
    }

    SDL_RenderPresent(renderer);
}


void sdl_handle_events(SparseGrid *grid) {

    SDL_Event e;

    while (SDL_WaitEventTimeout(&e, GAME_UPDATE_INTERVAL)) {
        switch(e.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_SPACE) {
                    if (pause) {
                        pause = 0;
                    } else {
                        pause = 1;
                    }
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
            
                if (e.button.button == SDL_BUTTON_LEFT) {
                    unsigned int x = e.button.x / CELL_SIZE;
                    unsigned int y = e.button.y / CELL_SIZE;

                    Cell *cell = sparse_grid_get_cell(grid, x, y);
                    if (cell) {
                        sparse_grid_delete_cell(grid, x, y);

                    } else {
                        sparse_grid_add_cell(grid, x, y);
                    }
                    sdl_render_grid(grid);
                }

                break;

            default:
                break;
        }
        
    }
    

}