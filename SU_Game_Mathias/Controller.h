#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Hero.h"
#include "Fjende.h"
#include "Grotte.h"
#include <string>
#include <QtSql>
#include <QSqlDatabase>

class Controller
{
public:
    Controller(Hero hero, Fjende fjende);

    void waitForEnter();

    void printHeros();          //Printer heros

    void saveHero();            //Gemmer hero

    void printHeroStats();      //Printer hero stats

    void loadHero(int heroNumber);  //Loader hero

    void addEmemies();              //Tilføjer fjender

    void printEnemies();            //Printer fjender

    int fight(int enemyNumber);

    void printGrotter();

    int fightCave(int caveNumber);

    void setHero(Hero hero);

private:
    Hero mHero;
    Fjende mFjende;
    Grotte mGrotte;
    QSqlQuery mQuery;
};

#endif // CONTROLLER_H
