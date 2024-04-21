#ifndef FJENDE_H
#define FJENDE_H
#include <string>
#include <QtSql>
#include <QSqlDatabase>
#include "Karekter.h"

class Fjende : public Karekter
{
public:
    Fjende();

    unsigned int getXpGain();       //Getter funktion til xp_gain

    void addEmemies();              //Tilføjer fjender

    void printEnemies();            //Printer fjender

    void setEnemyStats(unsigned int enemyIndeks);       //Sætter den valgte enemies stats

private:
    unsigned int mXpGain;
    QSqlQuery mQuery;

};

#endif // FJENDE_H
