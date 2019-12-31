#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
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
    
    for(int i=0; i<path.size(); i++)
    {
        cout << "(" << path[i].first << "," << path[i].second << ")" << endl;
    }
    
    return 0;
}

vector<pair<int,int>> dijkstra(vector<vector<pair<int, int>>> grid, pair<int,int> startIndex, pair<int,int> endIndex)
{
    Coordinate* initialPosition = new Coordinate(0, startIndex.first, startIndex.second);
    Coordinate* finalPosition;
    
    list<pair<int,int>> traversals;
    traversals.push_back(make_pair(-1,0));
    traversals.push_back(make_pair(0,1));
    traversals.push_back(make_pair(1,0));
    traversals.push_back(make_pair(0,-1));
    
    // Visited grid
    vector<bool> tempRow(50, false);
    vector<vector<bool>> visitedGrid(50, tempRow);
    
    // Set up queue for starting index of the algorithm
    priority_queue<pair<int,Coordinate*>> queue;
    queue.push(make_pair(initialPosition->getCost(), initialPosition));
    
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
            finalPosition = currentIndex;
            break;
        }
        else
        {
            list<pair<int,int>>::iterator listItr;
            for(listItr = traversals.begin(); listItr != traversals.end(); listItr++)
            {
                int nextPositionX = currentIndex->getPosition().first + (*listItr).first;
                int nextPositionY = currentIndex->getPosition().second + (*listItr).second;
                
                int newCost = -currentIndex->getCost() + 1;
                
                // If next position is in the grid and it has not been visited before
                if(checkInGrid(grid.size(), grid[0].size(), nextPositionX, nextPositionY) && !visitedGrid[nextPositionX][nextPositionY])
                {
                    Coordinate* temp = new Coordinate(newCost, nextPositionX, nextPositionY);
                    temp->previous = currentIndex;
                    
                    queue.push(make_pair(-newCost, temp));
                }
                
                //Need to implement functionality for if the cost of current is less or more than previous if node has already been visited
                
                visitedGrid[currentIndex->getPosition().first][currentIndex->getPosition().second] = true;   
            }
        }
    }
    
    return createPath(finalPosition);
}

bool checkInGrid(int sizeX, int sizeY, int x, int y)
{
    if(x < 0 || y < 0 || x >= sizeX || y >= sizeY)
    {
        return false;
    }
    
    return true;
}

vector<pair<int,int>> createPath(Coordinate* finalPosition)
{
    Coordinate* temp = finalPosition;
    vector<pair<int,int>> path;
    
    while(temp != NULL)
    {
        pair<int,int> newEntry = temp->getPosition();
        path.push_back(newEntry);
        temp = temp->previous;
    }
    
    reverse(path.begin(), path.end());
    
    return path;
}
