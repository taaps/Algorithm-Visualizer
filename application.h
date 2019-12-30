#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
using namespace std;

// Function Declarations
vector<pair<int,int>> dijkstra(vector<vector<pair<int, int>>> grid, pair<int,int> start, pair<int,int> end);
vector<pair<int,int>> createPath();

#endif /* MAIN_H */

