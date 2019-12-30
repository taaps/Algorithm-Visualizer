#include <iostream>
#include <vector>
#include <bits/stdc++.h>
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
    path = dijkstra(grid, startIndex, endIndex);
    
    return 0;
}

vector<pair<int,int>> dijkstra(vector<vector<pair<int, int>>> grid, pair<int,int> startIndex, pair<int,int> endIndex)
{
    Coordinate* initial = new Coordinate(0, startIndex.first, startIndex.second);
    
    // Set up queue for starting index of the algorithm
    priority_queue<pair<int,Coordinate*>> queue;
    queue.push(make_pair(initial->getCost(), initial));
    
    while(!queue.empty())
    {
        pair<int,Coordinate*> poppedItem;
        poppedItem = queue.top();
        queue.pop();
        
        int cost = poppedItem.first;
        Coordinate* currentIndex = poppedItem.second;
        
        // If the end index is found
        if(currentIndex->getPosition().first == endIndex.first && 
                currentIndex->getPosition().second == endIndex.second)
        {
            
        }
        else
        {
            
        }
    }
    
    return createPath();
}

vector<pair<int,int>> createPath()
{
    ;
}
