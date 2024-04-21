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

    unsigned int getXpGain();

    void addEmemies();

    void printEnemies();

    void setEnemyStats(unsigned int enemyIndeks);

private:
    unsigned int mXpGain;
    QSqlQuery mQuery;

};

#endif // FJENDE_H
