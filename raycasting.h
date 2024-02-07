#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL.h>


void raycast(SDL_Renderer *renderer, double playerAngle, double playerX, double playerY, char *map, int mapWidth, int mapHeight);
int checkCollision(double x, double y);
int parseMap(const char *filename, char **map, int *mapWidth, int *mapHeight);
void drawMap(SDL_Renderer *renderer, char *map, int mapWidth, int mapHeight);


#endif /* RAYCASTING_H */
