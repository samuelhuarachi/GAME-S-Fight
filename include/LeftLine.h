#ifndef LEFTLINE_H
#define LEFTLINE_H

class LeftLine
{
public:
    LeftLine(double y, double speed);
    virtual ~LeftLine();

    void update(double delta_time);
    void draw();

    double getY() const;
    bool hasLeftScreen() const;

private:
    double y;
    double speed;
};

#endif // LEFTLINE_H
