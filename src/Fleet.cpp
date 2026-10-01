#include "Fleet.h"

#include <cmath>

static const double FORMATION_SPACING = 20.0;

Fleet::Fleet(double x, double y)
{
    center_x = x;
    center_y = y;
    speed = 333;
    min_x = 248;
    max_x = 548;
    ships.emplace_back(center_x, center_y);
    placeShips();

    //for (int i = 0; i < 8; ++i)
    //    ships.emplace_back(center_x, center_y);
    //placeShips();
}

void Fleet::update(bool move_left, bool move_right, double delta_time)
{
    if (move_right)
        center_x += speed * delta_time;

    if (move_left)
        center_x -= speed * delta_time;

    double limit = maxDx();
    if (center_x > max_x - limit)
        center_x = max_x - limit;
    if (center_x < min_x + limit)
        center_x = min_x + limit;

    placeShips();
}

void Fleet::draw()
{
    for (Ship& ship : ships)
        ship.draw();
}

void Fleet::addShip()
{
    ships.emplace_back(center_x, center_y);
    placeShips();
}

void Fleet::shoot(std::vector<Bullet>& bullets) const
{
    for (const Ship& ship : ships)
        bullets.push_back(ship.shoot());
}

void Fleet::placeShips()
{
    std::vector<Offset> offsets = offsetsFor((int)ships.size());
    for (size_t i = 0; i < ships.size(); ++i)
        ships[i].setPosition(center_x + offsets[i].x, center_y + offsets[i].y);
}

double Fleet::maxDx() const
{
    double max_dx = 0;
    std::vector<Offset> offsets = offsetsFor((int)ships.size());
    for (size_t i = 0; i < offsets.size(); ++i) {
        double ax = std::fabs(offsets[i].x);
        if (ax > max_dx)
            max_dx = ax;
    }
    return max_dx;
}

std::vector<Fleet::Offset> Fleet::offsetsFor(int count)
{
    std::vector<Offset> out;
    if (count <= 0)
        return out;

    double spacing = FORMATION_SPACING;
    double row_gap = spacing * std::sqrt(3.0) / 2.0;

    std::vector<int> rows;
    int remaining = count;
    int row_size = 1;
    while (remaining > 0) {
        int take = remaining < row_size ? remaining : row_size;
        rows.push_back(take);
        remaining -= take;
        ++row_size;
    }

    int num_rows = (int)rows.size();
    for (int row = 0; row < num_rows; ++row) {
        int ships_in_row = rows[row];
        double y = -(num_rows - 1 - row) * row_gap;
        double x0 = -(ships_in_row - 1) * spacing / 2.0;
        for (int col = 0; col < ships_in_row; ++col) {
            Offset offset;
            offset.x = x0 + col * spacing;
            offset.y = y;
            out.push_back(offset);
        }
    }

    return out;
}
