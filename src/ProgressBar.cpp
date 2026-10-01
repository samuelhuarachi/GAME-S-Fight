#include "ProgressBar.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

static const double TRACK_X1 = 28.0;
static const double TRACK_X2 = 46.0;
static const double TRACK_Y1 = 216.0;
static const double TRACK_Y2 = 384.0;
static const double INNER_X1 = 30.0;
static const double INNER_X2 = 44.0;
static const double INNER_Y1 = 218.0;
static const double INNER_Y2 = 382.0;

ProgressBar::ProgressBar(double x_offset)
{
    value = 1;
    destroyed = 0;
    this->x_offset = x_offset;
}

void ProgressBar::setValue(int new_value)
{
    if (new_value < 1)
        new_value = 1;
    if (new_value > 100)
        new_value = 100;
    value = new_value;
}

int ProgressBar::getValue() const
{
    return value;
}

int ProgressBar::addDestructions(int count)
{
    int ships = 0;
    destroyed += count;

    while (destroyed >= 20) {
        destroyed -= 20;
        ships += 1;
    }

    value = destroyed * 5;
    if (value < 1)
        value = 1;

    return ships;
}

void ProgressBar::reset()
{
    value = 1;
    destroyed = 0;
}

void ProgressBar::draw()
{
    al_draw_filled_rectangle(
        TRACK_X1 + x_offset, TRACK_Y1,
        TRACK_X2 + x_offset, TRACK_Y2,
        al_map_rgb(20, 20, 20)
    );
    al_draw_rectangle(
        TRACK_X1 + x_offset, TRACK_Y1,
        TRACK_X2 + x_offset, TRACK_Y2,
        al_map_rgb(255, 255, 255),
        1
    );

    double inner_height = INNER_Y2 - INNER_Y1;
    double fill_height = inner_height * (value / 100.0);
    double fill_top = INNER_Y2 - fill_height;

    al_draw_filled_rectangle(
        INNER_X1 + x_offset, fill_top,
        INNER_X2 + x_offset, INNER_Y2,
        al_map_rgb(80, 220, 120)
    );

    al_draw_filled_circle(
        (INNER_X1 + INNER_X2) / 2.0 + x_offset,
        fill_top,
        4,
        al_map_rgb(255, 255, 255)
    );

    double track_height = TRACK_Y2 - TRACK_Y1;
    int marks[4] = {25, 50, 75, 100};
    for (int i = 0; i < 4; ++i) {
        double mark_y = TRACK_Y2 - track_height * (marks[i] / 100.0);
        al_draw_filled_rectangle(
            TRACK_X2 + x_offset + 4, mark_y - 1,
            TRACK_X2 + x_offset + 12, mark_y + 1,
            al_map_rgb(255, 255, 255)
        );
    }
}
