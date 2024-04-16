#ifndef HERO_H
#define HERO_H
#include <string>
#include <QtSql>
#include <QSqlDatabase>


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

    void printHeros();

    void saveHero();


private:
    std::string mName;
    unsigned int mXp, mLevel, mStyrke, mSkade;
    int mHp;
    QSqlQuery mQuery;

};

#endif // HERO_H
