#include <iostream>
#include <vector>
#include "coordinate.h"

using namespace std;

Coordinate::Coordinate()
{
    this->cost = 0;
    this->position.first = -1;
    this->position.second = -1;
    this->previous = NULL;
}

Coordinate::Coordinate(double cost, int first, int second)
{
    this->cost = cost;
    this->position.first = first;
    this->position.second = second;
    this->previous = NULL;
}

Coordinate::~Coordinate()
{
    this->previous = NULL;
}

double Coordinate::getCost()
{
    return this->cost;
}

void Coordinate::setCost(double cost)
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
