#include "Enemy.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

static const double BULLET_RADIUS = 4.0;
static const double SHIP_RADIUS = 6.0;
static const double SCREEN_BOTTOM = 600.0;
static const double HURT_INTERVAL = 1.0;

static int next_enemy_id = 1;

Enemy::Enemy(double x, double y, double speed, double radius, int bullet_damage, int life)
{
    this->x = x;
    this->y = y;
    this->speed = speed;
    this->radius = radius;
    this->hurt_cooldown = 0;
    this->life = life;
    this->bullet_damage = bullet_damage;
    this->id = next_enemy_id;
    this->stopped = false;
    next_enemy_id += 1;
}

void Enemy::update(double delta_time)
{
    if (hurt_cooldown > 0)
        hurt_cooldown -= delta_time;

    if (stopped)
        return;

    y += speed * delta_time;
}

void Enemy::draw()
{
    ALLEGRO_COLOR color = al_map_rgb(160, 60, 200);
    if (isTough())
        color = al_map_rgb(220, 40, 40);
    if (life <= 50)
        color = al_map_rgb(255, 220, 0);

    al_draw_filled_circle(x, y, radius, color);
}

void Enemy::stop()
{
    stopped = true;
}

void Enemy::pauseHurt()
{
    hurt_cooldown = HURT_INTERVAL;
}

double Enemy::getX() const
{
    return x;
}

double Enemy::getY() const
{
    return y;
}

double Enemy::getRadius() const
{
    return radius;
}

int Enemy::getId() const
{
    return id;
}

bool Enemy::hasLeftScreen() const
{
    return y >= SCREEN_BOTTOM;
}

bool Enemy::hitsBullet(double bullet_x, double bullet_y) const
{
    double dx = x - bullet_x;
    double dy = y - bullet_y;
    double reach = radius + BULLET_RADIUS;
    return dx * dx + dy * dy <= reach * reach;
}

bool Enemy::hitsShip(double ship_x, double ship_y) const
{
    double dx = x - ship_x;
    double dy = y - ship_y;
    double reach = radius + SHIP_RADIUS;
    return dx * dx + dy * dy <= reach * reach;
}

bool Enemy::takeHit()
{
    if (life <= 0)
        return false;

    life -= bullet_damage;
    return life <= 0;
}

void Enemy::destroy()
{
    life = 0;
}

bool Enemy::isDestroyed() const
{
    return life <= 0;
}

bool Enemy::isTough() const
{
    return bullet_damage == 1;
}

bool Enemy::isStopped() const
{
    return stopped;
}

bool Enemy::canHurt() const
{
    return hurt_cooldown <= 0;
}
