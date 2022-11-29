#ifndef ARR_H
#define ARR_H

#include <opencv2/opencv.hpp>

using namespace cv;

class Arr
{
public:

    Arr();
    Arr(Rect ret);
    ~Arr();

    void updateTime();
    void update(Rect ret);

    Rect rect;
    bool alive;

private:
    long time;
    clock_t cstart, cend;

};

#endif // ARR_H
