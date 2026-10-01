#ifndef LEFTSECTOR_H
#define LEFTSECTOR_H

#include "Bullet.h"
#include "LeftLine.h"

#include <vector>

class Fleet;

class LeftSector
{
public:
    LeftSector(double x1, double x2);

    void update(double delta_time);
    void draw();
    int collide(std::vector<Bullet>& bullets);
    void damageFleet(Fleet& fleet);
    void reset();

private:
    std::vector<LeftLine> lines;
    double x1;
    double x2;
};

#endif
