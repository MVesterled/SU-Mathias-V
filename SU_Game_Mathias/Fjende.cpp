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
unsigned int Fjende::getXpGain(){
    return mXpGain;
}

//Indsætter fjenderne i database
void Fjende::addEmemies(){
    //Liste af enemies laves
    QList<QVariantList> enemies = {
            {"Goblin", 200, 4, 1},
            {"Cow", 400, 8, 2},
            {"Wizard", 700, 20, 3},
            {"Giant", 1200, 20, 4},
            {"Dragon", 3000, 100, 10},
            {"Pungrotten (BJ-Kongen)", 9999, 10, 87}};

       //SQL statement forberedes
        mQuery.prepare("INSERT INTO enemies (name, xp_gain, hp, styrke) VALUES (:name, :xp_gain, :hp, :styrke)");

        // Ranged based for loop der sætter ind i tabel
        for (const auto& enemy : enemies) {
            mQuery.bindValue(":name", enemy[0]);
            mQuery.bindValue(":xp_gain", enemy[1]);
            mQuery.bindValue(":hp", enemy[2]);
            mQuery.bindValue(":styrke", enemy[3]);
            mQuery.exec();
        }

}

//Funktion der printer enemies
void Fjende::printEnemies(){
    std::cout << "Fjender:" << std::endl;
        mQuery.exec("SELECT * FROM enemies"); // Hero er tabel.
        qDebug() << "Antal fjender:" << mQuery.size(); //printer antal tasks

        //Printer
        while (mQuery.next()) {
            int id = mQuery.value(0).toInt();
            QString name = mQuery.value(1).toString();
            int xpGain = mQuery.value(2).toInt();
            int hp = mQuery.value(3).toInt();
            int styrke = mQuery.value(4).toInt();



            qDebug() << "Id:" << id << "Navn:" << name << "Styrke:" << styrke << "XP_Gain:" << xpGain << "HP:" << hp;
        }
}

//Funktion der sætter enemy stats til de valgte stats
void Fjende::setEnemyStats(unsigned int enemyIndeks){
    //Select der skal returnere alt data på given fjende
    mQuery.prepare("SELECT name, xp_gain, hp, styrke FROM enemies WHERE id = :enemyIndeks;");
    mQuery.bindValue(":enemyIndeks", enemyIndeks); //Binder id
    mQuery.exec(); //Kører query

    //assigner værdier
    if (mQuery.next()) {
            QString name = mQuery.value("name").toString();
            int xpGain = mQuery.value("xp_gain").toInt();
            int hp = mQuery.value("hp").toInt();
            int styrke = mQuery.value("styrke").toInt();

            mName = name.toStdString();
            mXpGain = xpGain;
            mHp = hp;
            mStyrke = styrke;

        }
    }













