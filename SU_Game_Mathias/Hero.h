#ifndef HERO_H
#define HERO_H
#include <string>
#include <QtSql>
#include <QSqlDatabase>
#include "Karekter.h"


class Hero : public Karekter
{
public:
    Hero();

    Hero(std::string navn);

    void addXp(int xp);

    void addLevel(int level);

    void resetAfterFight();

    void printHeros();

    void saveHero();

    void printHeroStats();

private:
    unsigned int mXp, mLevel;
    QSqlQuery mQuery;

};

#endif // HERO_H
