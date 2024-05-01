#ifndef GROTTE_H
#define GROTTE_H
#include "Fjende.h"
#include "Hero.h"
#include <string>
#include <QtSql>
#include <QSqlDatabase>


class Grotte
{
public:
    Grotte();

    void loadGrotteFjender(const unsigned int grotteNr);

    void loadGrotteData(const unsigned int grotteNr);

    Fjende getFjende(const unsigned int fjendeNr) const;

    int getGold() const;
    std::string getName() const;

private:
    Fjende mFjender[3];
    int mGrotteId, mGold;
    std::string mName;
    QSqlQuery mQuery;
};

#endif // GROTTE_H
