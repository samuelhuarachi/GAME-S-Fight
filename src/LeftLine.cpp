#include "LeftLine.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

static const double SECTOR_X1 = 243.0;
static const double SECTOR_X2 = 301.0;
static const double SCREEN_BOTTOM = 600.0;

LeftLine::LeftLine(double y, double speed)
{
    this->y = y;
    this->speed = speed;
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

bool LeftLine::hasLeftScreen() const
{
    return y >= SCREEN_BOTTOM;
}

void LeftLine::draw()
{
    al_draw_line(
        SECTOR_X1, y,
        SECTOR_X2, y,
        al_map_rgb(255, 255, 255),
        1
    );
}
