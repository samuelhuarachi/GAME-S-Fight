#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
public:
    Enemy(double x, double y, double speed, double radius = 3.0, int bullet_damage = 100, int life = 100);

    void update(double delta_time);
    void draw();
    void stop();
    void resume();
    void pauseHurt();

    double getX() const;
    double getY() const;
    double getRadius() const;
    int getId() const;
    bool hasLeftScreen() const;
    bool hitsBullet(double bullet_x, double bullet_y, double bullet_radius) const;
    bool hitsShip(double ship_x, double ship_y) const;
    bool takeHit();
    void takeDamage(int amount);
    void boostSpeed(double extra);
    void destroy();
    bool isDestroyed() const;
    bool isTough() const;
    bool isStopped() const;
    bool canHurt() const;

private:
    double x;
    double y;
    double speed;
    double radius;
    double hurt_cooldown;
    int life;
    int max_life;
    int bullet_damage;
    int id;
    bool stopped;
};

#endif
