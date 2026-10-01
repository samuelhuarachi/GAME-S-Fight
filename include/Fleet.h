#ifndef FLEET_H
#define FLEET_H

#include "Ship.h"

#include <vector>

class Fleet
{
public:
    Fleet(double x, double y);

    void update(bool move_left, bool move_right, double delta_time);
    void draw();
    void addShip();
    void shoot(std::vector<Bullet>& bullets) const;

private:
    struct Offset {
        double x;
        double y;
    };

    void placeShips();
    double maxDx() const;
    static std::vector<Offset> offsetsFor(int count);

    double center_x;
    double center_y;
    double speed;
    double min_x;
    double max_x;
    std::vector<Ship> ships;
};

#endif
