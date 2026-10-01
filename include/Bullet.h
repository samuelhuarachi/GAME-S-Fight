#ifndef BULLET_H
#define BULLET_H

class Bullet
{
public:
    Bullet(double x, double y);
    Bullet(double x, double y, bool big);

    void update(double delta_time);
    void draw();

    double getX() const;
    double getY() const;
    double getRadius() const;
    void deactivate();
    bool isActive() const;
    bool isBig() const;
    static void upgradeSpeed();
    static void resetUpgrade();

private:
    double x;
    double y;
    double velocity_x;
    double velocity_y;
    double radius;
    bool active;
    bool big;
};

#endif // BULLET_H
