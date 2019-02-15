#ifndef _RANDOM_HEIGHT_H_
#define _RANDOM_HEIGHT_H_

#include <random>

using namespace std;

class RandomHeight
{
private:
    int maxLevel;
    float probability;

public:
    RandomHeight(const int maxLvl,const float prob);
    ~RandomHeight(){}
    int newLevel();
};


RandomHeight::RandomHeight(const int maxLvl,const float prob)
{
    //randomize();

    maxLevel = maxLvl;
    probability = prob;
}

int RandomHeight::newLevel()
{
    int tmpLvl = 1;

    while ((rand() * 1.0 / RAND_MAX) < probability && tmpLvl < maxLevel)
    {
        tmpLvl++;
    }

    return tmpLvl;
}
#endif