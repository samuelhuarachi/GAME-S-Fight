#include "Bullet.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

static const double PI = 3.14159265358979323846;

Bullet::Bullet(double x, double y)
{
    static bool seeded = false;
    if (!seeded) {
        std::srand((unsigned)std::time(0));
        seeded = true;
    }

    this->x = x;
    this->y = y;

    double speed = 800.0 + (std::rand() % 401);
    double degrees = (std::rand() % 5) - 2;
    double radians = degrees * PI / 180.0;
    this->velocity_x = std::sin(radians) * speed;
    this->velocity_y = -std::cos(radians) * speed;
    this->active = true;
}

void Bullet::update(double delta_time)
{
    if (!active)
        return;

    x += velocity_x * delta_time;
    y += velocity_y * delta_time;

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
