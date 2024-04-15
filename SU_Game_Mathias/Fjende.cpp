#include "Fjende.h"

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

void Fjende::addEmemies(){

}
