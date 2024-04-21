#include "Karekter.h"

Karekter::Karekter()
{
 mName = "";
}

std::string Karekter::getName(){
    return mName;
}

int Karekter::getHp(){
    return mHp;
}

//Tjekker om Karekter er i live
bool Karekter::isAlive(){
    return mHp > 0;
}

//Funktion der returnere den skade der skal gives
unsigned int Karekter::getDamage(){
    return mStyrke;
}

//Funktion der tager skade
void Karekter::takeDamage(int damage){
    mHp -= damage;
    if (mHp < 1){

    }
}
