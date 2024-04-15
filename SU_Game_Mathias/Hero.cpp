#include "Hero.h"
#include <iostream>

//default constructor
Hero::Hero()
{
    mName = "Kurt";
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























