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

    void addXp(int xp);         //tilføjer xp til hero

    void addLevel(int level);   //tilføjer level til hero

    void resetAfterFight();     //Resetter hp efter kamp


    unsigned int getXp() const;
    void setXp(unsigned int xp);

    unsigned int getLevel() const;
    void setLevel(unsigned int level);

private:
    unsigned int mXp, mLevel;
    QSqlQuery mQuery;

};

#endif // HERO_H
