#include "LeftSector.h"

#include "Fleet.h"

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
    for (LeftLine& line : lines) {
        if (line.isDestroyed())
            continue;
        line.draw();
    }
}

int LeftSector::collide(std::vector<Bullet>& bullets)
{
    int destroyed = 0;

    for (Bullet& bullet : bullets) {
        if (!bullet.isActive())
            continue;

        for (LeftLine& line : lines) {
            if (line.isDestroyed())
                continue;
            if (!line.hits(bullet.getX(), bullet.getY()))
                continue;

            bullet.deactivate();
            if (line.takeHit())
                destroyed += 1;
            break;
        }
    }

    lines.erase(
        std::remove_if(
            lines.begin(),
            lines.end(),
            [](const LeftLine& line) {
                return line.isDestroyed();
            }
        ),
        lines.end()
    );

    return destroyed;
}

void LeftSector::damageFleet(Fleet& fleet)
{
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].isDestroyed())
            continue;
        if (!fleet.collideWith(lines[i]))
            continue;

        int last = (int)i + 6;
        if (last >= (int)lines.size())
            last = (int)lines.size() - 1;

        for (int j = (int)i; j <= last; ++j)
            lines[j].destroy();
    }

    lines.erase(
        std::remove_if(
            lines.begin(),
            lines.end(),
            [](const LeftLine& line) {
                return line.isDestroyed();
            }
        ),
        lines.end()
    );

    fleet.removeDead();
}

void LeftSector::reset()
{
    lines.clear();
}
