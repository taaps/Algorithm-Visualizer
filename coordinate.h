#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include <vector>
using namespace std;

class Coordinate
{
private:
    double cost;
    pair<int,int> position;
    
public:
    Coordinate* previous;
    
    Coordinate();
    Coordinate(double cost, int first, int second);
    ~Coordinate();
    double getCost();
    void setCost(double cost);
    pair<int,int> getPosition();
    void setPosition(int first, int second);
};

#endif /* COORDINATE_H */
