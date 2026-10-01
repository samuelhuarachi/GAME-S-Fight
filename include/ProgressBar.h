#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

class ProgressBar
{
public:
    ProgressBar(double x_offset = 0);

    void setValue(int new_value);
    int getValue() const;
    int addDestructions(int count);
    void reset();
    void draw();

private:
    int value;
    int destroyed;
    double x_offset;
};

#endif
