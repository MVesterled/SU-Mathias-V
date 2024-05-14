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

    unsigned int getXpGain() const;       //Getter funktion til xp_gain
    void setXpGain(unsigned int xpGain);

    void setEnemyStats(unsigned int enemyIndeks);       //Sætter den valgte enemies stats

    std::string getElement() const;

private:
    unsigned int mXpGain;
    std::string mElement;
    QSqlQuery mQuery;

};

#endif // FJENDE_H
