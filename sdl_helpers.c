#include "sdl_helpers.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 1000
#define WINDOW_LENGTH 1000
#define CELL_SIZE 20

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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    pause_mx = SDL_CreateMutex();
    pause_cond = SDL_CreateCond(); 
}

void sdl_quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyCond(pause_cond);
    SDL_DestroyMutex(pause_mx);

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

void toggle_pause(int *paused) {
    SDL_LockMutex(pause_mx);
    *paused = 0;
    SDL_CondSignal(pause_cond);
    SDL_UnlockMutex(pause_mx);
}

void sdl_handle_events(SparseGrid *grid, int *running, int *paused) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                *running = 0;
                toggle_pause(paused);
                break;
            
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_SPACE) {
                    toggle_pause(paused);
                } else if (e.key.keysym.sym == SDLK_ESCAPE) {
                    *running = 0;
                    toggle_pause(paused);
                }

                break;

            default:
                break;
        }
    }
}