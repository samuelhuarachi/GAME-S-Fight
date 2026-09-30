#ifndef SHIP_H
#define SHIP_H

class Ship
{
public:
    Ship(double x, double y);

    void update(bool move_left, bool move_right, double delta_time);
    void draw();

    double getX() const;
    double getY() const;

private:
    double x;
    double y;
    double speed;
};

#endif
