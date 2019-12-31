#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include "coordinate.h"
using namespace std;

// Function Declarations
vector<pair<int,int>> dijkstra(vector<vector<pair<int, int>>> grid, pair<int,int> start, pair<int,int> end);
bool checkInGrid(int gridX, int gridY, int x, int y);
vector<pair<int,int>> createPath(Coordinate* finalPosition);

#endif /* MAIN_H */
