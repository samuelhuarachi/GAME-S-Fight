#include "MiddleSector.h"

#include "Fleet.h"

#include <algorithm>
#include <cstdlib>

static const double ENEMY_SPEED = 40.0;
static const double PACK_CLEAR = 12.0;
static const double PACK_X1 = 314.0;
static const double PACK_X2 = 482.0;
static const double SMALL_RADIUS = 3.0;
static const double TOUGH_RADIUS = 12.0;
static const double TOUGH_X1 = 319.0;
static const double TOUGH_X2 = 477.0;
static const int TOUGH_BULLET_DAMAGE = 1;
static const int TOUGH_LIFE = 300;
static const int PACK_COUNT = 14;
static const int PLACE_TRIES = 20;

static bool tooClose(const std::vector<Enemy>& enemies, double x, double y, double radius)
{
    for (const Enemy& enemy : enemies) {
        double dx = enemy.getX() - x;
        double dy = enemy.getY() - y;
        double min_distance = enemy.getRadius() + radius;
        if (dx * dx + dy * dy < min_distance * min_distance)
            return true;
    }

    return false;
}

MiddleSector::MiddleSector()
{
    tough_timer = 0;
    rollToughWait();
}

void MiddleSector::rollToughWait()
{
    tough_wait = 20.0 + (std::rand() % 11);
}

void MiddleSector::spawnRow()
{
    int x_span = (int)(PACK_X2 - PACK_X1) + 1;

    for (int n = 0; n < PACK_COUNT; ++n) {
        for (int attempt = 0; attempt < PLACE_TRIES; ++attempt) {
            double x = PACK_X1 + (std::rand() % x_span);
            double y = -16.0 + (std::rand() % 17);
            if (tooClose(enemies, x, y, SMALL_RADIUS))
                continue;

            enemies.emplace_back(x, y, ENEMY_SPEED);
            break;
        }
    }
}

void MiddleSector::spawnTough()
{
    int x_span = (int)(TOUGH_X2 - TOUGH_X1) + 1;

    for (int attempt = 0; attempt < PLACE_TRIES; ++attempt) {
        double x = TOUGH_X1 + (std::rand() % x_span);
        double y = -TOUGH_RADIUS;
        if (tooClose(enemies, x, y, TOUGH_RADIUS))
            continue;

        enemies.emplace_back(x, y, ENEMY_SPEED, TOUGH_RADIUS, TOUGH_BULLET_DAMAGE, TOUGH_LIFE);
        tough_timer = 0;
        rollToughWait();
        return;
    }
}

void MiddleSector::update(double delta_time, Fleet& fleet)
{
    bool top_clear = true;
    for (const Enemy& enemy : enemies) {
        if (enemy.getY() < PACK_CLEAR) {
            top_clear = false;
            break;
        }
    }

    if (enemies.empty() || top_clear)
        spawnRow();

    tough_timer += delta_time;
    if (tough_timer >= tough_wait)
        spawnTough();

    for (Enemy& enemy : enemies)
        enemy.update(delta_time);

    for (const Enemy& enemy : enemies) {
        if (!enemy.hasLeftScreen())
            continue;
        if (enemy.isTough()) {
            if (!enemy.isStopped())
                fleet.killAll();
            continue;
        }
        fleet.damageRandomShip(1);
    }

    enemies.erase(
        std::remove_if(
            enemies.begin(),
            enemies.end(),
            [](const Enemy& enemy) {
                return enemy.hasLeftScreen();
            }
        ),
        enemies.end()
    );

    fleet.removeDead();
}

void MiddleSector::draw()
{
    for (Enemy& enemy : enemies) {
        if (enemy.isDestroyed())
            continue;
        enemy.draw();
    }
}

void MiddleSector::collide(std::vector<Bullet>& bullets)
{
    for (Bullet& bullet : bullets) {
        if (!bullet.isActive())
            continue;

        for (Enemy& enemy : enemies) {
            if (enemy.isDestroyed())
                continue;
            if (!enemy.hitsBullet(bullet.getX(), bullet.getY(), bullet.getRadius()))
                continue;

            if (bullet.isBig()) {
                if (enemy.isTough()) {
                    enemy.takeDamage(100);
                    bullet.deactivate();
                    break;
                }

                enemy.destroy();
                continue;
            }

            bullet.deactivate();
            enemy.takeHit();
            break;
        }
    }

    enemies.erase(
        std::remove_if(
            enemies.begin(),
            enemies.end(),
            [](const Enemy& enemy) {
                return enemy.isDestroyed();
            }
        ),
        enemies.end()
    );
}

void MiddleSector::damageFleet(Fleet& fleet)
{
    for (Enemy& enemy : enemies) {
        if (enemy.isDestroyed())
            continue;

        if (enemy.isTough()) {
            bool apply = enemy.canHurt();
            if (fleet.hurtOverlapping(enemy, apply)) {
                enemy.stop();
                if (apply)
                    enemy.pauseHurt();
            } else {
                enemy.resume();
            }
            continue;
        }

        if (!fleet.collideWith(enemy))
            continue;

        enemy.destroy();
    }

    enemies.erase(
        std::remove_if(
            enemies.begin(),
            enemies.end(),
            [](const Enemy& enemy) {
                return enemy.isDestroyed();
            }
        ),
        enemies.end()
    );

    fleet.removeDead();
}

void MiddleSector::reset()
{
    enemies.clear();
    tough_timer = 0;
    rollToughWait();
}
