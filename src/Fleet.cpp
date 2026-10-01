#include "Fleet.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>

static const double FORMATION_SPACING = 20.0;

Fleet::Fleet(double x, double y)
{
    center_x = x;
    center_y = y;
    speed = 333;
    min_x = 248;
    max_x = 548;
    //ships.emplace_back(center_x, center_y);
    //placeShips();

    for (int i = 0; i < 3; ++i)
        ships.emplace_back(center_x, center_y);
    placeShips();
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
    if (ships.size() >= 12)
        return;

    ships.emplace_back(center_x, center_y);
    placeShips();
}

void Fleet::shoot(std::vector<Bullet>& bullets) const
{
    for (const Ship& ship : ships)
        bullets.push_back(ship.shoot());
}

void Fleet::shootBig(std::vector<Bullet>& bullets) const
{
    bullets.push_back(Bullet(center_x, center_y, true));
}

bool Fleet::collideWith(const LeftLine& line)
{
    bool hit = false;

    for (Ship& ship : ships) {
        if (!ship.isAlive())
            continue;
        if (ship.wasHitBy(line.getId()))
            continue;
        if (!line.hitsCircle(ship.getX(), ship.getY(), 6))
            continue;

        ship.rememberHit(line.getId());
        ship.takeDamage(15);
        hit = true;
    }

    return hit;
}

bool Fleet::collideWith(const Enemy& enemy)
{
    bool hit = false;

    for (Ship& ship : ships) {
        if (!ship.isAlive())
            continue;
        if (ship.wasHitByEnemy(enemy.getId()))
            continue;
        if (!enemy.hitsShip(ship.getX(), ship.getY()))
            continue;

        ship.rememberEnemyHit(enemy.getId());
        ship.takeDamage(15);
        hit = true;
    }

    return hit;
}

bool Fleet::hurtOverlapping(const Enemy& enemy, bool apply_damage)
{
    bool touching = false;

    for (Ship& ship : ships) {
        if (!ship.isAlive())
            continue;
        if (!enemy.hitsShip(ship.getX(), ship.getY()))
            continue;

        touching = true;
        if (apply_damage)
            ship.takeDamage(15);
    }

    return touching;
}

void Fleet::damageRandomShip(int amount)
{
    std::vector<size_t> living;

    for (size_t i = 0; i < ships.size(); ++i) {
        if (ships[i].isAlive())
            living.push_back(i);
    }

    if (living.empty())
        return;

    size_t pick = living[std::rand() % living.size()];
    ships[pick].takeDamage(amount);
}

void Fleet::killAll()
{
    for (Ship& ship : ships)
        ship.takeDamage(100);
}

void Fleet::removeDead()
{
    ships.erase(
        std::remove_if(
            ships.begin(),
            ships.end(),
            [](const Ship& ship) {
                return !ship.isAlive();
            }
        ),
        ships.end()
    );

    if (!ships.empty())
        placeShips();
}

void Fleet::reset()
{
    ships.clear();
    for (int i = 0; i < 3; ++i)
        ships.emplace_back(center_x, center_y);
    placeShips();
}

int Fleet::shipCount() const
{
    return (int)ships.size();
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
