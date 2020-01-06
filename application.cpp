#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <bits/stdc++.h>
#include <limits>
#include <cmath>
#include "application.h"
#include "coordinate.h"
using namespace std;

int main(int argc, char** argv) 
{
    vector<Coordinate*> tempRow(50, NULL);
    vector<vector<Coordinate*>> grid(50, tempRow);
    int gridRowSize = 50;
    int gridColSize = 50;
    
    pair<int, int> startIndex(0, 0);
    pair<int, int> endIndex(0, 3);
    
    //Call Path-Finding Algorithm
    vector<pair<int,int>> pathDijkstra;
    vector<pair<int,int>> pathAStar;
    pathDijkstra = dijkstra(grid, gridRowSize, gridColSize, startIndex, endIndex);
    pathAStar = astar(grid, gridRowSize, gridColSize, startIndex, endIndex);
    
    return 0;
}

vector<pair<int,int>> dijkstra(vector<vector<Coordinate*>> grid, int gridRowSize, 
        int gridColSize, pair<int,int> startIndex, pair<int,int> endIndex)
{
    Coordinate* initialPosition = new Coordinate(0, startIndex.first, startIndex.second);
    Coordinate* finalPosition;
    
    list<pair<int,int>> traversals;
    traversals.push_back(make_pair(-1,0));
    traversals.push_back(make_pair(0,1));
    traversals.push_back(make_pair(1,0));
    traversals.push_back(make_pair(0,-1));
    
    // Visited grid
    vector<bool> tempVisitedRow(50, false);
    vector<vector<bool>> visitedGrid(50, tempVisitedRow);
    
    // Cost to travel to a node
    vector<double> tempCostRow(50, numeric_limits<double>::max());
    vector<vector<double>> calculatedCostGrid(50, tempCostRow);
    
    // Set up queue for starting index of the algorithm
    priority_queue<pair<double,Coordinate*>> queue;
    queue.push(make_pair(initialPosition->getCost(), initialPosition));
    visitedGrid[startIndex.first][startIndex.second] = true;
    calculatedCostGrid[startIndex.first][startIndex.second] = 0;
    
    while(!queue.empty())
    {
        pair<double,Coordinate*> poppedItem;
        poppedItem = queue.top();
        queue.pop();
        
        double cost = poppedItem.first;
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
                
                if(checkInGrid(gridRowSize, gridColSize, nextPositionX, nextPositionY))
                {
                    double newCost = currentIndex->getCost() + 1;
                    bool visited = visitedGrid[nextPositionX][nextPositionY];

                    if(!visited)
                    {
                        if(newCost < calculatedCostGrid[nextPositionX][nextPositionY])
                        {
                            Coordinate* node;
                            
                            if(grid[nextPositionX][nextPositionY] != NULL)
                            {
                                node = grid[nextPositionX][nextPositionY];
                                node->previous = currentIndex;
                                node->setCost(newCost);
                                
                                calculatedCostGrid[nextPositionX][nextPositionY] = newCost;
                            }
                            else
                            {
                                node = new Coordinate(newCost, nextPositionX, nextPositionY);
                                node->previous = currentIndex;
                                
                                grid[nextPositionX][nextPositionY] = node;
                                visitedGrid[nextPositionX][nextPositionY] = true;   
                                calculatedCostGrid[nextPositionX][nextPositionY] = newCost;
                            }
                            
                            queue.push(make_pair(-node->getCost(), node));
                        }
                    }
                }
            }
        }
    }

    return createPath(finalPosition);
}

vector<pair<int,int>> astar(vector<vector<Coordinate*>> grid, int gridRowSize, 
        int gridColSize, pair<int,int> startIndex, pair<int,int> endIndex)
{
    Coordinate* initialPosition = new Coordinate(0, startIndex.first, startIndex.second);
    Coordinate* finalPosition;
    
    list<pair<int,int>> traversals;
    traversals.push_back(make_pair(-1,0));
    traversals.push_back(make_pair(0,1));
    traversals.push_back(make_pair(1,0));
    traversals.push_back(make_pair(0,-1));
    
    // Visited grid
    vector<bool> tempVisitedRow(50, false);
    vector<vector<bool>> visitedGrid(50, tempVisitedRow);
    
    // Cost to travel to a node
    vector<double> tempCostRow(50, numeric_limits<double>::max());
    vector<vector<double>> calculatedCostGrid(50, tempCostRow);
    
    // Set up queue for starting index of the algorithm
    priority_queue<pair<double,Coordinate*>> queue;
    queue.push(make_pair(initialPosition->getCost(), initialPosition));
    visitedGrid[startIndex.first][startIndex.second] = true;
    calculatedCostGrid[startIndex.first][startIndex.second] = 0;
    
    while(!queue.empty())
    {
        pair<double,Coordinate*> poppedItem;
        poppedItem = queue.top();
        queue.pop();
        
        double cost = poppedItem.first;
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
                
                if(checkInGrid(gridRowSize, gridColSize, nextPositionX, nextPositionY))
                {
                    double newCost = currentIndex->getCost() + heuristic(make_pair(nextPositionX, nextPositionY), endIndex);
                    bool visited = visitedGrid[nextPositionX][nextPositionY];

                    if(!visited)
                    {
                        if(newCost < calculatedCostGrid[nextPositionX][nextPositionY])
                        {
                            Coordinate* node;
                            
                            if(grid[nextPositionX][nextPositionY] != NULL)
                            {
                                node = grid[nextPositionX][nextPositionY];
                                node->previous = currentIndex;
                                node->setCost(newCost);
                                
                                calculatedCostGrid[nextPositionX][nextPositionY] = newCost;
                            }
                            else
                            {
                                node = new Coordinate(newCost, nextPositionX, nextPositionY);
                                node->previous = currentIndex;
                                
                                grid[nextPositionX][nextPositionY] = node;
                                visitedGrid[nextPositionX][nextPositionY] = true;   
                                calculatedCostGrid[nextPositionX][nextPositionY] = newCost;
                            }
                            
                            queue.push(make_pair(-node->getCost(), node));
                        }
                    }
                }
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

void freeCoordinateGrid(vector<vector<Coordinate*>> grid, int gridRowSize, int gridColSize)
{
    for (int i=0; i<gridRowSize; i++)
    {
        for(int j=0; j<gridColSize; j++)
        {
            Coordinate* temp = grid[i][j];
            
            if(temp != NULL)
            {
                free(temp);
            }
        }
    }
}

double heuristic(pair<int,int> currentIndex, pair<int,int> finalIndex)
{
    return sqrt((finalIndex.second-currentIndex.second)*(finalIndex.second-currentIndex.second)
            + (finalIndex.first-currentIndex.first)*(finalIndex.first-currentIndex.first));
}
