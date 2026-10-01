#ifndef SHIP_H
#define SHIP_H

#include "Bullet.h"

class Ship
{
public:
    Ship(double x, double y);

    void setPosition(double new_x, double new_y);
    void draw();
    Bullet shoot() const;

    double getX() const;
    double getY() const;

private:
    double x;
    double y;
};

#endif
