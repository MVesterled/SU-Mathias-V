#ifndef FJENDE_H
#define FJENDE_H
#include <string>

class Fjende
{
public:
    Fjende();

    Fjende(std::string navn, int hp, unsigned int mXpGain, unsigned int mSkade);

    unsigned int xpGain(int xp);

    void takeDamage(int damage);

    int dealDamage(int damage);

    bool isAlive();

    void addEmemies();

private:
    std::string mName;
    unsigned int mXpGain, mSkade;
    int mHp;

};

#endif // FJENDE_H
