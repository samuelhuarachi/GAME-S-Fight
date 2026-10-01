#include "Ship.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

static int next_ship_id = 1;

Ship::Ship(double x, double y)
{
    this->x = x;
    this->y = y;
    this->id = next_ship_id;
    next_ship_id += 1;
    this->life = 100;
}

void Ship::setPosition(double new_x, double new_y)
{
    x = new_x;
    y = new_y;
}

void Ship::draw()
{
    ALLEGRO_COLOR color = al_map_rgb(255, 60, 60);
    if (life > 60)
        color = al_map_rgb(80, 220, 120);
    else if (life > 30)
        color = al_map_rgb(255, 220, 0);

    al_draw_circle(x, y, 6, color, 2);
}

Bullet Ship::shoot() const
{
    return Bullet(x, y);
}

void Ship::takeDamage(int amount)
{
    life -= amount;
    if (life < 0)
        life = 0;
}

void Ship::rememberHit(int line_id)
{
    hit_line_ids.push_back(line_id);
}

void Ship::rememberEnemyHit(int enemy_id)
{
    hit_enemy_ids.push_back(enemy_id);
}

double Ship::getX() const
{
    return x;
}

double Ship::getY() const
{
    return y;
}

bool Ship::isAlive() const
{
    return life > 0;
}

bool Ship::wasHitBy(int line_id) const
{
    for (size_t i = 0; i < hit_line_ids.size(); ++i) {
        if (hit_line_ids[i] == line_id)
            return true;
    }
    return false;
}

bool Ship::wasHitByEnemy(int enemy_id) const
{
    for (size_t i = 0; i < hit_enemy_ids.size(); ++i) {
        if (hit_enemy_ids[i] == enemy_id)
            return true;
    }
    return false;
}
