#ifndef SHIP_H
#define SHIP_H

#include "Bullet.h"

#include <vector>

class Ship
{
public:
    Ship(double x, double y);

    void setPosition(double new_x, double new_y);
    void draw();
    Bullet shoot() const;
    void takeDamage(int amount);
    void rememberHit(int line_id);
    void rememberEnemyHit(int enemy_id);

    double getX() const;
    double getY() const;
    bool isAlive() const;
    bool wasHitBy(int line_id) const;
    bool wasHitByEnemy(int enemy_id) const;

private:
    double x;
    double y;
    int id;
    int life;
    std::vector<int> hit_line_ids;
    std::vector<int> hit_enemy_ids;
};

#endif
