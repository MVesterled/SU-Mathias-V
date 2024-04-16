#ifndef FJENDE_H
#define FJENDE_H
#include <string>
#include <QtSql>
#include <QSqlDatabase>

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

    void printEnemies();

private:
    std::string mName;
    unsigned int mXpGain, mSkade;
    int mHp;
    QSqlQuery mQuery;

};

#endif // FJENDE_H
