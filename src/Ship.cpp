#include "Ship.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

Ship::Ship(double x, double y)
{
    this->x = x;
    this->y = y;
}

void Ship::setPosition(double new_x, double new_y)
{
    x = new_x;
    y = new_y;
}

void Ship::draw()
{
    al_draw_circle(x, y, 6, al_map_rgb(255, 0, 0), 2);
}

Bullet Ship::shoot() const
{
    return Bullet(x, y);
}

double Ship::getX() const
{
    return x;
}

double Ship::getY() const
{
    return y;
}
