#ifndef KAREKTER_H
#define KAREKTER_H
#include <string>
#include <iostream>

class Karekter
{
public:
    Karekter();
    std::string getName();

    int getHp();

    bool isAlive();

    unsigned int getDamage();

    void takeDamage(int damage);

protected:
    std::string mName;
    int mHp;
    unsigned int mStyrke;
};

#endif // KAREKTER_H
