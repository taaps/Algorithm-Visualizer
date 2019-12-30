#include <iostream>
#include <vector>
#include <utility>
#include "application.h"
#include "coordinate.h"
using namespace std;

int main(int argc, char** argv) 
{
    pair<int, int> tempValue;
    tempValue.first = 0;
    tempValue.second = 0;
    
    vector<pair<int, int>> tempRow(50, tempValue);
    vector<vector<pair<int, int>>> grid(50, tempRow);
    
    for(int i=0; i<50; i++)
    {
        for(int j=0; j<50; j++)
        {
            grid[i][j].first = i;
            grid[i][j].second = j;
        }
    }
    
    pair<int, int> startIndex(0, 0);
    pair<int, int> endIndex(4, 0);
    
    //Call Path-Finding Algorithm
    vector<pair<int,int>> path;
    path = dijkstra(startIndex, endIndex);
    
    return 0;
}

vector<pair<int,int>> dijkstra(pair<int,int> start, pair<int,int> end)
{
    
}