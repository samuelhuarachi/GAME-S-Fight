#ifndef LEFTSECTOR_H
#define LEFTSECTOR_H

#include "LeftLine.h"

#include <vector>

class LeftSector
{
public:
    LeftSector();

    void update(double delta_time);
    void draw();

private:
    std::vector<LeftLine> lines;
};

#endif
