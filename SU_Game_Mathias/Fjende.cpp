#include "Fjende.h"
#include <iostream>

//Default constructor
Fjende::Fjende()
{
    mName = "bot";
    mHp = 1;
    mXpGain = 1;
    mStyrke = 1;
}

//Funktion der returnere xp som hero skal have
unsigned int Fjende::getXpGain() const{
    return mXpGain;
}

void Fjende::setXpGain(unsigned int xpGain){
    mXpGain = xpGain;
}

//Funktion der sætter enemy stats til de valgte stats
void Fjende::setEnemyStats(unsigned int enemyIndeks){
    //Select der skal returnere alt data på given fjende
    mQuery.prepare("SELECT name, xp_gain, hp, styrke, element FROM enemies WHERE id = :enemyIndeks;");
    mQuery.bindValue(":enemyIndeks", enemyIndeks); //Binder id
    mQuery.exec(); //Kører query

    //assigner værdier
    if (mQuery.next()) {
            QString name = mQuery.value("name").toString();
            int xpGain = mQuery.value("xp_gain").toInt();
            int hp = mQuery.value("hp").toInt();
            int styrke = mQuery.value("styrke").toInt();
            QString element = mQuery.value("element").toString();

            mName = name.toStdString();
            mXpGain = xpGain;
            mHp = hp;
            mStyrke = styrke;
            mElement = element.toStdString();

        }
    }

std::string Fjende::getElement() const{
    return mElement;
}











