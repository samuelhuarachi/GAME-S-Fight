#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

class ProgressBar
{
public:
    ProgressBar();

    void setValue(int new_value);
    int getValue() const;
    int addDestructions(int count);
    void draw();

private:
    int value;
    int destroyed;
};

#endif
