#ifndef LEFTSECTOR_H
#define LEFTSECTOR_H

#include "Bullet.h"
#include "LeftLine.h"

#include <vector>

class Fleet;

class LeftSector
{
public:
    LeftSector();

    void update(double delta_time);
    void draw();
    int collide(std::vector<Bullet>& bullets);
    void damageFleet(Fleet& fleet);
    void reset();

private:
    std::vector<LeftLine> lines;
};

#endif
