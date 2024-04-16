#include "Fjende.h"
#include <iostream>

//Default constructor
Fjende::Fjende()
{
    mName = "bot";
    mHp = 1;
    mXpGain = 1;
    mSkade = 1;
}

//constructor med initilizer list
Fjende::Fjende(std::string navn, int hp, unsigned int xpGain, unsigned int skade)
    : mName(navn), mHp(hp), mXpGain(xpGain), mSkade(skade)
{}

//Funktion der returnere xp som hero skal have
unsigned int Fjende::xpGain(int xp){
    return mXpGain;
}

//Tager skade
void Fjende::takeDamage(int damage){
    mHp -= damage;
}

//Giver skade
int Fjende::dealDamage(int damage){
    return mSkade;
}

//Tjekker om fjende er i live
bool Fjende::isAlive(){
    return mHp < 0;
}

//Indsætter fjenderne i database
void Fjende::addEmemies(){
    //Liste af enemies laves
    QList<QVariantList> enemies = {
            {"Goblin", 100, 4, 1},
            {"Cow", 200, 8, 2},
            {"Wizard", 400, 20, 3},
            {"Giant", 500, 20, 4},
            {"Dragon", 3000, 100, 10} };

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
