#include "Enemy.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <cstdio>

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
    this->max_life = life;
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

    if (isTough()) {
        double remaining = 0;
        if (max_life > 0)
            remaining = (double)life / (double)max_life;

        color = al_map_rgb(255, 255, 255);
        if (remaining > 0.20)
            color = al_map_rgb(255, 255, 140);
        if (remaining > 0.40)
            color = al_map_rgb(255, 220, 0);
        if (remaining > 0.60)
            color = al_map_rgb(255, 140, 0);
        if (remaining > 0.80)
            color = al_map_rgb(220, 40, 40);
    }

    al_draw_filled_circle(x, y, radius, color);

    if (!isTough())
        return;

    static ALLEGRO_FONT* font = al_create_builtin_font();
    char label[16];
    std::snprintf(label, sizeof(label), "%d", life);
    al_draw_text(
        font,
        al_map_rgb(255, 255, 255),
        x,
        y - radius - 10,
        ALLEGRO_ALIGN_CENTRE,
        label
    );
}

void Enemy::stop()
{
    stopped = true;
}

void Enemy::resume()
{
    stopped = false;
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

bool Enemy::hitsBullet(double bullet_x, double bullet_y, double bullet_radius) const
{
    double dx = x - bullet_x;
    double dy = y - bullet_y;
    double reach = radius + bullet_radius;
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

void Enemy::takeDamage(int amount)
{
    if (life <= 0)
        return;

    life -= amount;
    if (life < 0)
        life = 0;
}

void Enemy::boostSpeed(double extra)
{
    speed += extra;
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
