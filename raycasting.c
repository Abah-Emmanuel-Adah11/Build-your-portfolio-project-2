#include "raycasting.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265
#define TILE_SIZE 32

void raycast(SDL_Renderer *renderer, double playerAngle, double playerX, double playerY, char *map, int mapWidth, int mapHeight) {
	/* Implement raycasting here to draw walls */
   	 /* For now, let's just draw a simple wall */
    double wallAngle = fmod(playerAngle, 360); // Ensure angle is within 0-360 degrees

    if (wallAngle >= 0 && wallAngle < 90) {
        // Wall facing EAST, draw in blue
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    } else if (wallAngle >= 90 && wallAngle < 180) {
        // Wall facing SOUTH, draw in green
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    } else if (wallAngle >= 180 && wallAngle < 270) {
        // Wall facing WEST, draw in red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    } else {
        // Wall facing NORTH, draw in yellow
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    }

    SDL_Rect wall = {100, 100, 50, 200}; // Example wall
    SDL_RenderFillRect(renderer, &wall);

    // Draw player
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect player = {playerX, playerY, 5, 5}; // Example player size
    SDL_RenderFillRect(renderer, &player);

    // Draw map
    drawMap(renderer, map, mapWidth, mapHeight);
}

int checkCollision(double x, double y) {
    // Example collision detection logic
    // Check if the player's new position collides with any walls
    // For now, always return 0 (no collision)
    return 0;
}

int parseMap(const char *filename, char **map, int *mapWidth, int *mapHeight) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file '%s' for reading\n", filename);
        return 0;
    }

    int maxWidth = 0;
    int height = 0;
    char ch;

    // Count the number of characters per line to determine the width of the map
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            height++;
            if (maxWidth == 0) {
                maxWidth = ftell(file);
            }
        }
    }

    // Calculate the width of the map (excluding newline characters)
    int width = maxWidth / height;

    // Allocate memory for the map
    *map = (char *)malloc(width * height * sizeof(char));
    if (!*map) {
        fclose(file);
        fprintf(stderr, "Error: Unable to allocate memory for map\n");
        return 0;
    }

    // Reset file pointer to beginning of file
    fseek(file, 0, SEEK_SET);

    // Read the map data from the file
    int index = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch != '\n') {
            (*map)[index++] = ch;
        }
    }

    // Close the file
    fclose(file);

    // Set output parameters
    *mapWidth = width;
    *mapHeight = height;

    return 1;
}

void drawMap(SDL_Renderer *renderer, char *map, int mapWidth, int mapHeight) {
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            if (map[y * mapWidth + x] == 'W') {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Wall color
                SDL_Rect wall = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_RenderFillRect(renderer, &wall);
            }
        }
    }
}

