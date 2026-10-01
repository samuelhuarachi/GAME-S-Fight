#ifndef FLEET_H
#define FLEET_H

#include "Enemy.h"
#include "LeftLine.h"
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
    void shootBig(std::vector<Bullet>& bullets) const;
    bool collideWith(const LeftLine& line);
    bool collideWith(const Enemy& enemy);
    bool hurtOverlapping(const Enemy& enemy, bool apply_damage);
    void damageRandomShip(int amount);
    void killAll();
    void removeDead();
    void reset();
    int shipCount() const;

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
