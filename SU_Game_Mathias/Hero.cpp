#include "Hero.h"
#include <iostream>

//default constructor
Hero::Hero()
{
    mName = "Dummy";
    mXp = 0;
    mLevel = 1;
    mStyrke = 1;
    mSkade = 1;
    mHp = 10;
}

//constructor med navn
Hero::Hero(std::string navn){
    mName = navn;
    mXp = 0;
    mLevel = 1;
    mStyrke = 2;
    mSkade = 1;
    mHp = 10;
}

//Funktion der giver hero xp
void Hero::addXp(int xp){
    mXp += xp;
    if (mXp > mLevel*1000){
        mXp -= (mLevel*1000);
        addLevel(1);
    }
}

//funktion der håndterer level up
void Hero::addLevel(int level){
    mLevel += level;
    mStyrke += 1;
    mHp += 2;
}

//Funktion der tager skade
void Hero::takeDamage(int damage){
    mHp -= damage;
    if (mHp < 1){

    }
}

//Funktion der returnere den skade der skal gives
int Hero::dealDamage(int damage){
    return mStyrke;
}

//Funktion der gør klar til ny kamp
void Hero::resetAfterFight(){
    mHp = 10+(mLevel*2-2);
}

//Tjekker om hero er i live
bool Hero::isAlive(){
    return mHp < 0;
}

void Hero::printHeros(){
    std::cout << "Heroes:" << std::endl;
        mQuery.exec("SELECT * FROM hero"); // Hero er tabel.
        qDebug() << "Antal heros:" << mQuery.size(); //printer antal tasks

        //Printer
        while (mQuery.next()) {
            int id = mQuery.value(0).toInt();
            int level = mQuery.value(1).toInt();
            int styrke = mQuery.value(2).toInt();
            int xp = mQuery.value(3).toInt();
            int hp = mQuery.value(4).toInt();
            QString name = mQuery.value(5).toString();


            qDebug() << "Id:" << id << "Navn:" << name << "Level:" << level << "Styrke:" << styrke << "XP:" << xp << "HP:" << hp;
        }
}


void Hero::saveHero(){
    mQuery.prepare("INSERT INTO hero (level, styrke, xp, hp, name) VALUES (:level, :styrke, :xp, :hp, :name)");

    // Sætter værdier
    mQuery.bindValue(":level", mLevel); // Example level value
    mQuery.bindValue(":styrke", mStyrke); // Example styrke value
    mQuery.bindValue(":xp", mXp); // Example xp value
    mQuery.bindValue(":hp", mHp); // Example hp value
    mQuery.bindValue(":name", QString::fromStdString(mName)); // Example name value
    mQuery.exec();
}


















