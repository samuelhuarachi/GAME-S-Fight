#ifndef MIDDLESECTOR_H
#define MIDDLESECTOR_H

#include "Bullet.h"
#include "Enemy.h"

#include <vector>

class Fleet;

class MiddleSector
{
public:
    MiddleSector();

    void update(double delta_time, Fleet& fleet);
    void draw();
    void collide(std::vector<Bullet>& bullets);
    void damageFleet(Fleet& fleet);
    void reset();

private:
    void spawnRow();
    void spawnTough();
    void rollToughWait();

    std::vector<Enemy> enemies;
    double tough_timer;
    double tough_wait;
};

#endif
