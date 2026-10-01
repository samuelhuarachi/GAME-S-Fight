#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

class ProgressBar
{
public:
    ProgressBar();

    void setValue(int new_value);
    int getValue() const;
    void draw();

private:
    int value;
};

#endif
