#include "Grotte.h"

Grotte::Grotte()
{
}

//funktion til at indlæse fjendedata fra database
void Grotte::loadGrotteFjender(const unsigned int grotteNr){
        int enemyIndeks = grotteNr*3-2; //temp til at tage rigtigt indeks i enemy liste
        mFjender[0].setEnemyStats(enemyIndeks);
        mFjender[1].setEnemyStats(enemyIndeks+1);
        mFjender[2].setEnemyStats(enemyIndeks+2);
}

//funktion til at indlæse grottedata fra database
void Grotte::loadGrotteData(const unsigned int grotteNr){
    //Select der skal returnere alt data på given grotte
    mQuery.prepare("SELECT name, gold FROM grotter WHERE grotte_id = :grotte_id;");
    mQuery.bindValue(":grotte_id", grotteNr); //Binder id
    mQuery.exec(); //Kører query

    //assigner værdier
    if (mQuery.next()) {
            QString name = mQuery.value("name").toString();
            int gold = mQuery.value("gold").toInt();

            std::string nameTemp = name.toStdString();
            mName = nameTemp;
            mGold = gold;
        }
}

//returnerer en af de 3 fjender
Fjende Grotte::getFjende(const unsigned int fjendeNr) const{
    return mFjender[fjendeNr];
}

//getter til gold
int Grotte::getGold() const{
    return mGold;
}

//getter til navn
std::string Grotte::getName() const{
    return mName;
}
