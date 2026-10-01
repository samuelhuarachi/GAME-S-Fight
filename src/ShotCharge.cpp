#include "ShotCharge.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

static const double FILL_TIME = 1.0;
static const double BAR_X1 = 340.0;
static const double BAR_X2 = 460.0;
static const double BAR_Y1 = 16.0;
static const double BAR_Y2 = 28.0;
static const double INNER_X1 = 342.0;
static const double INNER_X2 = 458.0;
static const double INNER_Y1 = 18.0;
static const double INNER_Y2 = 26.0;

ShotCharge::ShotCharge()
{
    value = 0;
}

void ShotCharge::update(double delta_time)
{
    value += (100.0 / FILL_TIME) * delta_time;
    if (value > 100)
        value = 100;
}

void ShotCharge::empty()
{
    value = 0;
}

void ShotCharge::reset()
{
    value = 0;
}

bool ShotCharge::isFull() const
{
    return value >= 100;
}

void ShotCharge::draw()
{
    al_draw_filled_rectangle(
        BAR_X1, BAR_Y1,
        BAR_X2, BAR_Y2,
        al_map_rgb(20, 20, 20)
    );
    al_draw_rectangle(
        BAR_X1, BAR_Y1,
        BAR_X2, BAR_Y2,
        al_map_rgb(255, 255, 255),
        1
    );

    double inner_width = INNER_X2 - INNER_X1;
    double fill_width = inner_width * (value / 100.0);
    ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
    if (isFull())
        color = al_map_rgb(255, 220, 0);

    if (fill_width > 0) {
        al_draw_filled_rectangle(
            INNER_X1, INNER_Y1,
            INNER_X1 + fill_width, INNER_Y2,
            color
        );
    }
}
