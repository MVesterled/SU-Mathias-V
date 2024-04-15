#ifndef HERO_H
#define HERO_H
#include <string>


class Hero
{
public:
    Hero();

    Hero(std::string navn);

    void addXp(int xp);

    void addLevel(int level);

    void takeDamage(int damage);

    int dealDamage(int damage);

    void resetAfterFight();

    bool isAlive();

private:
    std::string mName;
    unsigned int mXp, mLevel, mStyrke, mSkade;
    int mHp;

};

#endif // HERO_H
