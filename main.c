#include <stdio.h>
#include <SDL.h>
#include "raycasting.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    int quit = 0;
    double playerAngle = 0.0; // Player's initial angle
    double playerX = 100.0;   // Player's initial X position
    double playerY = 100.0;   // Player's initial Y position
    char *map;
    int mapWidth, mapHeight;


    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    /* Create window */
    window = SDL_CreateWindow("Raycasting 3D Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    /* Create renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /* Parse map */
    if (!parseMap("map.txt", &map, &mapWidth, &mapHeight)) {
        // Handle error
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /* Main loop */
    while (!quit) {
        /* Handle events */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                // Rotate left
                if (event.key.keysym.sym == SDLK_LEFT) {
                    playerAngle -= 5; // Adjust the angle by 5 degrees to the left
                }
                // Rotate right
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                    playerAngle += 5; // Adjust the angle by 5 degrees to the right
                }
                // Move forward
                else if (event.key.keysym.sym == SDLK_w) {
                    // Calculate new position
                    double newX = playerX + cos(playerAngle * PI / 180); // Move along X axis
                    double newY = playerY + sin(playerAngle * PI / 180); // Move along Y axis
                    
                    // Check for collision with walls
                    if (!checkCollision(newX, newY)) {
                        // No collision, update player position
                        playerX = newX;
                        playerY = newY;
                    }
                }
                // Move backward
                else if (event.key.keysym.sym == SDLK_s) {
                    // Calculate new position
                    double newX = playerX - cos(playerAngle * PI / 180); // Move along X axis
                    double newY = playerY - sin(playerAngle * PI / 180); // Move along Y axis
                    
                    // Check for collision with walls
                    if (!checkCollision(newX, newY)) {
                        // No collision, update player position
                        playerX = newX;
                        playerY = newY;
                    }
                }
            }
        }

        /* Raycasting with updated player angle and position */
        raycast(renderer, playerAngle, playerX, playerY, map, mapWidth, mapHeight);
    }

    /* Cleanup */
    free(map);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
