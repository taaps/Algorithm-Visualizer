#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <queue>
#include <limits>
#include <cmath>
#include "application.h"
#include "coordinate.h"
#include <SDL.h> 

using namespace std;

const int GRID_CELL_SIZE = 10;
const int GRID_WIDTH = 75;
const int GRID_HEIGHT = 75;

// Added the plus one so window can hold the last grid line
const int WINDOW_WIDTH = (GRID_WIDTH * GRID_CELL_SIZE) + 1;
const int WINDOW_HEIGHT = (GRID_HEIGHT * GRID_CELL_SIZE) + 1;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) < 0)
    {
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(window, "Algorithm Visualizer");

    SDL_Event windowEvent;
    SDL_Color grid_background = { 255, 255, 255, 255 }; // White
    SDL_Color grid_line_color = { 224, 224, 224, 255 }; // Black
    SDL_Color grid_visited_colour = { 0, 0, 0, 255 }; // Black
    SDL_Color final_path_colour = { 255, 153, 204, 255 }; //Pink

    // Set up drawing variables
    SDL_Rect grid_visited = { -1, -1, GRID_CELL_SIZE, GRID_CELL_SIZE };
    bool drawInitial = false;
    bool calledPathFinding = false;

    // Set up path finding variables
    vector<Coordinate*> tempRow(GRID_WIDTH, NULL);
    vector<vector<Coordinate*>> grid(GRID_HEIGHT, tempRow);

    vector<double> tempCostRow(GRID_WIDTH, 1);
    vector<vector<double>> costGrid(GRID_HEIGHT, tempCostRow);

    pair<int, int> startIndex(0, 0);
    pair<int, int> endIndex(74, 74);

    // Set up blocks in the grid
    vector<bool> tempBlockRow(GRID_WIDTH, true);
    vector<vector<bool>> blockGrid(GRID_HEIGHT, tempBlockRow);

    for (int i = 40; i < 41; i++)
    {
        for (int j = 20; j < 60; j++)
        {
            blockGrid[i][j] = false;
        }
    }

    // Window will keep running unitl the user closes it
    while (true)
    {
        // If the user requests for closing the window
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }

        // Draw grid background
        SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g, grid_background.b, grid_background.a);
        SDL_RenderClear(renderer);

        // Draw grid lines
        SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g, grid_line_color.b, grid_line_color.a);

        if (!drawInitial)
        {
            // Draw vertical lines
            for (int x = 0; x < 1 + GRID_WIDTH * GRID_CELL_SIZE; x += GRID_CELL_SIZE) 
            {
                SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);
            }

            // Draw horizontal lines
            for (int y = 0; y < 1 + GRID_WIDTH * GRID_CELL_SIZE; y += GRID_CELL_SIZE) 
            {
                SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
            }

            // Draw initial and final starting points
            grid_visited.x = startIndex.first * GRID_CELL_SIZE;
            grid_visited.y = startIndex.second * GRID_CELL_SIZE;
            SDL_SetRenderDrawColor(renderer, grid_visited_colour.r, grid_visited_colour.g, grid_visited_colour.b, grid_visited_colour.a);
            SDL_RenderFillRect(renderer, &grid_visited);

            grid_visited.x = endIndex.first * GRID_CELL_SIZE;
            grid_visited.y = endIndex.second * GRID_CELL_SIZE;
            SDL_SetRenderDrawColor(renderer, grid_visited_colour.r, grid_visited_colour.g, grid_visited_colour.b, grid_visited_colour.a);
            SDL_RenderFillRect(renderer, &grid_visited);

            // Draw blocks in the grid
            for (int i = 0; i < GRID_WIDTH; i++)
            {
                for (int j = 0; j < GRID_HEIGHT; j++)
                {
                    if (!blockGrid[i][j])
                    {
                        grid_visited.x = i * GRID_CELL_SIZE;
                        grid_visited.y = j * GRID_CELL_SIZE;
                        SDL_SetRenderDrawColor(renderer, grid_visited_colour.r, grid_visited_colour.g, grid_visited_colour.b, grid_visited_colour.a);
                        SDL_RenderFillRect(renderer, &grid_visited);
                    }
                }
            }

            SDL_RenderPresent(renderer);
            drawInitial = true;
        }

        if (!calledPathFinding)
        {
            vector<pair<int, int>> path;
            //path = dijkstra(grid, costGrid, GRID_WIDTH, GRID_HEIGHT, startIndex, endIndex, renderer, blockGrid);
            path = astar(grid, GRID_WIDTH, GRID_HEIGHT, startIndex, endIndex, renderer, blockGrid);

            grid_visited.x = endIndex.first * GRID_CELL_SIZE;
            grid_visited.y = endIndex.second * GRID_CELL_SIZE;
            SDL_SetRenderDrawColor(renderer, grid_visited_colour.r, grid_visited_colour.g, grid_visited_colour.b, grid_visited_colour.a);
            SDL_RenderFillRect(renderer, &grid_visited);
            SDL_RenderPresent(renderer);

            // Draw the path found
            for (int i = 1; i < path.size()-1; i++)
            {
                // Draw final path nodes
                grid_visited.x = path[i].first * GRID_CELL_SIZE;
                grid_visited.y = path[i].second * GRID_CELL_SIZE;
                SDL_SetRenderDrawColor(renderer, final_path_colour.r, final_path_colour.g, final_path_colour.b, final_path_colour.a);
                SDL_RenderFillRect(renderer, &grid_visited);

                SDL_RenderPresent(renderer);
                SDL_Delay(20);
            }

            calledPathFinding = true;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

vector<pair<int,int>> dijkstra(vector<vector<Coordinate*>> grid, vector<vector<double>> costGrid, 
        int gridRowSize, int gridColSize, pair<int,int> startIndex, pair<int,int> endIndex, SDL_Renderer* renderer, vector<vector<bool>> blockGrid)
{
    Coordinate* initialPosition = new Coordinate(0, startIndex.first, startIndex.second);
    Coordinate* finalPosition = NULL;

    // Window screen variables
    SDL_Color grid_visited_colour = { 0, 128, 255, 255 }; // Blue
    SDL_Rect grid_visited = { -1, -1, GRID_CELL_SIZE, GRID_CELL_SIZE };
    
    list<pair<int,int>> traversals;
    traversals.push_back(make_pair(1, 0));
    traversals.push_back(make_pair(0, 1));
    traversals.push_back(make_pair(0, -1));
    traversals.push_back(make_pair(-1,0));
    
    // Visited grid
    vector<bool> tempVisitedRow(GRID_WIDTH, false);
    vector<vector<bool>> visitedGrid(GRID_HEIGHT, tempVisitedRow);
    bool initialNode = false;
    
    // Cost to travel to a node
    vector<double> tempCostRow(GRID_WIDTH, numeric_limits<double>::max());
    vector<vector<double>> calculatedCostGrid(GRID_HEIGHT, tempCostRow);
    
    // Set up queue for starting index of the algorithm
    priority_queue<pair<double,Coordinate*>> queue;
    queue.push(make_pair(initialPosition->getCost(), initialPosition));
    visitedGrid[startIndex.first][startIndex.second] = true;
    calculatedCostGrid[startIndex.first][startIndex.second] = 0;
    
    while(!queue.empty())
    {
        SDL_Delay(5);
        pair<double,Coordinate*> poppedItem;
        poppedItem = queue.top();
        queue.pop();

        if (initialNode)
        {
            // Draw visited nodes
            grid_visited.x = poppedItem.second->getPosition().first * GRID_CELL_SIZE;
            grid_visited.y = poppedItem.second->getPosition().second * GRID_CELL_SIZE;
            SDL_SetRenderDrawColor(renderer, grid_visited_colour.r, grid_visited_colour.g, grid_visited_colour.b, grid_visited_colour.a);
            SDL_RenderFillRect(renderer, &grid_visited);
            SDL_RenderPresent(renderer);
        }

        initialNode = true;
        
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
                    if (blockGrid[nextPositionX][nextPositionY])
                    {
                        double newCost = currentIndex->getCost() + costGrid[nextPositionX][nextPositionY];
                        bool visited = visitedGrid[nextPositionX][nextPositionY];

                        if (!visited)
                        {
                            if (newCost < calculatedCostGrid[nextPositionX][nextPositionY])
                            {
                                Coordinate* node;

                                if (grid[nextPositionX][nextPositionY] != NULL)
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
    }

    return createPath(finalPosition);
}

vector<pair<int,int>> astar(vector<vector<Coordinate*>> grid, int gridRowSize,
        int gridColSize, pair<int,int> startIndex, pair<int,int> endIndex, SDL_Renderer* renderer, vector<vector<bool>> blockGrid)
{
    Coordinate* initialPosition = new Coordinate(0, startIndex.first, startIndex.second);
    Coordinate* finalPosition = NULL;

    // Window screen variables
    SDL_Color grid_visited_colour = { 0, 128, 255, 255 }; // Blue
    SDL_Rect grid_visited = { -1, -1, GRID_CELL_SIZE, GRID_CELL_SIZE };
    
    list<pair<int,int>> traversals;
    traversals.push_back(make_pair(-1,0));
    traversals.push_back(make_pair(0,1));
    traversals.push_back(make_pair(1,0));
    traversals.push_back(make_pair(0,-1));
    
    // Visited grid
    vector<bool> tempVisitedRow(GRID_WIDTH, false);
    vector<vector<bool>> visitedGrid(GRID_HEIGHT, tempVisitedRow);
    bool initialNode = false;
    
    // Cost to travel to a node
    vector<double> tempCostRow(GRID_WIDTH, numeric_limits<double>::max());
    vector<vector<double>> calculatedCostGrid(GRID_HEIGHT, tempCostRow);
    
    // Set up queue for starting index of the algorithm
    priority_queue<pair<double,Coordinate*>> queue;
    queue.push(make_pair(initialPosition->getCost(), initialPosition));
    visitedGrid[startIndex.first][startIndex.second] = true;
    calculatedCostGrid[startIndex.first][startIndex.second] = 0;
    
    while(!queue.empty())
    {
        SDL_Delay(10);
        pair<double,Coordinate*> poppedItem;
        poppedItem = queue.top();
        queue.pop();

        if (initialNode)
        {
            // Draw visited nodes
            grid_visited.x = poppedItem.second->getPosition().first * GRID_CELL_SIZE;
            grid_visited.y = poppedItem.second->getPosition().second * GRID_CELL_SIZE;
            SDL_SetRenderDrawColor(renderer, grid_visited_colour.r, grid_visited_colour.g, grid_visited_colour.b, grid_visited_colour.a);
            SDL_RenderFillRect(renderer, &grid_visited);
            SDL_RenderPresent(renderer);
        }

        initialNode = true;
        
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
                    if (blockGrid[nextPositionX][nextPositionY])
                    {
                        double newCost = heuristic(make_pair(nextPositionX, nextPositionY), endIndex);
                        bool visited = visitedGrid[nextPositionX][nextPositionY];

                        if (!visited)
                        {
                            if (newCost < calculatedCostGrid[nextPositionX][nextPositionY])
                            {
                                Coordinate* node;

                                if (grid[nextPositionX][nextPositionY] != NULL)
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
