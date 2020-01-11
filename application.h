#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include "coordinate.h"
#include <SDL.h>
using namespace std;

// Function Declarations
vector<pair<int,int>> dijkstra(vector<vector<Coordinate*>> grid, vector<vector<double>> costGrid, 
        int gridRowSize, int gridColSize, pair<int,int> startIndex, pair<int,int> endIndex, SDL_Renderer* renderer);
vector<pair<int,int>> astar(vector<vector<Coordinate*>> grid, int gridRowSize, 
        int gridColSize, pair<int,int> startIndex, pair<int,int> endIndex);
bool checkInGrid(int gridX, int gridY, int x, int y);
vector<pair<int,int>> createPath(Coordinate* finalPosition);
void freeCoordinateGrid(vector<vector<Coordinate*>> grid, int gridRowSize, int gridColSize);
double heuristic(pair<int,int> currentIndex, pair<int,int> finalIndex);

#endif /* MAIN_H */
