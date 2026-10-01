#ifndef SHOTCHARGE_H
#define SHOTCHARGE_H

class ShotCharge
{
public:
    ShotCharge();

    void update(double delta_time);
    void empty();
    void reset();
    void draw();
    bool isFull() const;

private:
    double value;
};

#endif
