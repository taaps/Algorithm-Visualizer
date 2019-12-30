#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include <vector>
using namespace std;

class Coordinate
{
private:
    int cost;
    pair<int,int> position;
    
public:
    Coordinate* previous;
    
    Coordinate();
    int getCost();
    void setCost(int cost);
    pair<int,int> getPosition();
    void setPosition(int first, int second);
};

#endif /* COORDINATE_H */

