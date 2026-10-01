#include "Bullet.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

static const double PI = 3.14159265358979323846;
static const double BIG_RADIUS = 12.0;
static int speed_bonus = 0;
static int spread_degrees = 15;

static double rollSpeed()
{
    static bool seeded = false;
    if (!seeded) {
        std::srand((unsigned)std::time(0));
        seeded = true;
    }

    double speed = 800.0 + speed_bonus + (std::rand() % 401);
    if (speed > 2000.0)
        speed = 2000.0;
    return speed;
}

Bullet::Bullet(double x, double y)
{
    this->x = x;
    this->y = y;

    double speed = rollSpeed();
    int span = spread_degrees * 2 + 1;
    double degrees = (std::rand() % span) - spread_degrees;
    double radians = degrees * PI / 180.0;
    this->velocity_x = std::sin(radians) * speed;
    this->velocity_y = -std::cos(radians) * speed;
    this->radius = 4;
    this->active = true;
    this->big = false;
}

Bullet::Bullet(double x, double y, bool big)
{
    this->x = x;
    this->y = y;

    double speed = rollSpeed();
    this->velocity_x = 0;
    this->velocity_y = -speed;
    this->radius = BIG_RADIUS;
    this->active = true;
    this->big = big;
}

void Bullet::update(double delta_time)
{
    if (!active)
        return;

    x += velocity_x * delta_time;
    y += velocity_y * delta_time;

    if (y < 0 || x - radius < 237 || x + radius > 559)
        active = false;
}

void Bullet::draw()
{
    if (!active)
        return;

    al_draw_filled_circle(
        x,
        y,
        radius,
        al_map_rgb(255, 255, 255)
    );
}

double Bullet::getX() const
{
    return x;
}

double Bullet::getY() const
{
    return y;
}

double Bullet::getRadius() const
{
    return radius;
}

void Bullet::deactivate()
{
    active = false;
}

bool Bullet::isActive() const
{
    return active;
}

bool Bullet::isBig() const
{
    return big;
}

void Bullet::upgradeSpeed()
{
    speed_bonus += 200;
}

void Bullet::resetUpgrade()
{
    speed_bonus = 0;
}

void Bullet::setSpread(int degrees)
{
    if (degrees < 1)
        degrees = 1;
    spread_degrees = degrees;
}
