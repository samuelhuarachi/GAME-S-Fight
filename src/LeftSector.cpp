#include "LeftSector.h"

#include <algorithm>

static const double LINE_GAP = 10.0;
static const double LINE_SPEED = 50.0;

LeftSector::LeftSector()
{
}

void LeftSector::update(double delta_time)
{
    if (lines.empty() || lines.back().getY() >= LINE_GAP)
        lines.emplace_back(0, LINE_SPEED);

    for (LeftLine& line : lines)
        line.update(delta_time);

    lines.erase(
        std::remove_if(
            lines.begin(),
            lines.end(),
            [](const LeftLine& line) {
                return line.hasLeftScreen();
            }
        ),
        lines.end()
    );
}

void LeftSector::draw()
{
    for (LeftLine& line : lines)
        line.draw();
}
