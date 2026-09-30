#include "Ship.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

Ship::Ship(double x, double y)
{
    this->x = x;
    this->y = y;
    this->speed = 333;
}

void Ship::update(bool move_left, bool move_right, double delta_time)
{
    if (move_right) {
        x += speed * delta_time;
    }

    if (move_left) {
        x -= speed * delta_time;
    }

    if (x > 548) {
        x = 548;
    }

    if (x < 248) {
        x = 248;
    }
}

void Ship::draw()
{
    al_draw_circle(
        x,
        y,
        8,
        al_map_rgb(255, 0, 0),
        3
    );
}

double Ship::getX() const
{
    return x;
}

double Ship::getY() const
{
    return y;
}
