#include "Bullet.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

Bullet::Bullet(double x, double y)
{
    this->x = x;
    this->y = y;
    this->speed = 500;
    this->active = true;
}

void Bullet::update(double delta_time)
{
    if (!active)
        return;

    // Move para cima
    y -= speed * delta_time;

    // Chegou ao topo
    if (y < 0) {
        active = false;
    }
}

void Bullet::draw()
{
    if (!active)
        return;

    al_draw_filled_circle(
        x,
        y,
        4,
        al_map_rgb(255, 255, 255)
    );
}

bool Bullet::isActive() const
{
    return active;
}
