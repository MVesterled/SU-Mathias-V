#include "Karekter.h"

Karekter::Karekter()
{
 mName = "";
}

std::string Karekter::getName() const{
    return mName;
}

void Karekter::setName(std::string& name){
    mName = name;
}

int Karekter::getHp() const{
    return mHp;
}

void Karekter::setHp(int hp){
    mHp = hp;
}

//Tjekker om Karekter er i live
bool Karekter::isAlive(){
    return mHp > 0;
}

//Funktion der returnere den skade der skal gives
unsigned int Karekter::getDamage() const{
    return mStyrke;
}

void Karekter::setDamage(unsigned int styrke){
    mStyrke = styrke;
}

//Funktion der tager skade
void Karekter::takeDamage(int damage){
    mHp += damage;
    if (mHp < 1){

    }
}
