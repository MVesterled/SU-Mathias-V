#ifndef KAREKTER_H
#define KAREKTER_H
#include <string>
#include <iostream>

class Karekter
{
public:
    Karekter();
    std::string getName() const;
    void setName(std::string& name);

    int getHp() const;
    void setHp(int hp);

    bool isAlive();

    unsigned int getDamage() const;
    void setDamage(unsigned int styrke);

    void takeDamage(int damage);

protected:
    std::string mName;
    int mHp;
    unsigned int mStyrke;
};

#endif // KAREKTER_H
