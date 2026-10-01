#include "LeftLine.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

static const double SCREEN_BOTTOM = 600.0;

static int next_line_id = 1;

LeftLine::LeftLine(double y, double speed, double x1, double x2)
{
    this->y = y;
    this->speed = speed;
    this->x1 = x1;
    this->x2 = x2;
    this->life = 3;
    this->id = next_line_id;
    next_line_id += 1;
}

LeftLine::~LeftLine()
{
}

void LeftLine::update(double delta_time)
{
    y += speed * delta_time;
}

double LeftLine::getY() const
{
    return y;
}

int LeftLine::getId() const
{
    return id;
}

bool LeftLine::hasLeftScreen() const
{
    return y >= SCREEN_BOTTOM;
}

bool LeftLine::hits(double bullet_x, double bullet_y, double radius) const
{
    if (bullet_x < x1 - radius || bullet_x > x2 + radius)
        return false;

    double dy = bullet_y - y;
    if (dy < 0)
        dy = -dy;
    return dy <= radius;
}

bool LeftLine::hitsCircle(double cx, double cy, double radius) const
{
    double closest_x = cx;
    if (closest_x < x1)
        closest_x = x1;
    if (closest_x > x2)
        closest_x = x2;

    double dx = cx - closest_x;
    double dy = cy - y;
    return dx * dx + dy * dy <= radius * radius;
}

bool LeftLine::takeHit()
{
    if (life <= 0)
        return false;

    life -= 1;
    return life <= 0;
}

void LeftLine::destroy()
{
    life = 0;
}

bool LeftLine::isDestroyed() const
{
    return life <= 0;
}

void LeftLine::draw()
{
    ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
    if (life == 2)
        color = al_map_rgb(255, 220, 0);
    if (life == 1)
        color = al_map_rgb(255, 60, 60);

    al_draw_line(
        x1, y,
        x2, y,
        color,
        1
    );
}
