#ifndef BULLET_H
#define BULLET_H

class Bullet
{
public:
    Bullet(double x, double y);

    void update(double delta_time);
    void draw();

    double getX() const;
    double getY() const;
    void deactivate();
    bool isActive() const;

private:
    double x;
    double y;
    double velocity_x;
    double velocity_y;
    bool active;
};

#endif // BULLET_H
