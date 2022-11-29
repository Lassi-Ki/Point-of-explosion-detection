#include "arr.h"


Arr::Arr()
{
    cstart = clock();
    cend = clock();

    alive = true;
    this->rect = Rect(0, 0, 0, 0);
}

Arr::Arr(Rect ret)
{
    cstart = clock();
    cend = clock();

    alive = true;
    this->rect = ret;
}

Arr::~Arr()
{

}


void Arr::updateTime()
{
    cend = clock();
    time = cend - cstart;
    if (time > 1000)
    {
        alive = false;
    }
}

void Arr::update(Rect ret)
{
    this->rect = ret;
}
