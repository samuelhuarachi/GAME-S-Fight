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
    int getId() const;
    bool hasLeftScreen() const;
    bool hits(double bullet_x, double bullet_y) const;
    bool hitsCircle(double cx, double cy, double radius) const;
    bool takeHit();
    void destroy();
    bool isDestroyed() const;

private:
    double y;
    double speed;
    int life;
    int id;
};

#endif // LEFTLINE_H
