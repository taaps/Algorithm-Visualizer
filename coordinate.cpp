#include <iostream>
#include <vector>
#include "coordinate.h"

using namespace std;

Coordinate::Coordinate()
{
    cost = 0;
    position.first = -1;
    position.second = -1;
    previous = NULL;
}

Coordinate::Coordinate(int cost, int first, int second)
{
    this->cost = cost;
    this->position.first = first;
    this->position.second = second;
    this->previous = NULL;
}

int Coordinate::getCost()
{
    return this->cost;
}

void Coordinate::setCost(int cost)
{
    this->cost = cost;
}

pair<int,int> Coordinate::getPosition()
{
    return this->position;
}

void Coordinate::setPosition(int first, int second)
{
    this->position.first = first;
    this->position.second = second;
}
