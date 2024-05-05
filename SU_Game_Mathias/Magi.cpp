#include "Magi.h"

Magi::Magi()
{

}

void Magi::setStyrke(int styrke){
    mStyrke = styrke;
}
int Magi::getStyrke() const{
    return mStyrke;
}

void Magi::setSelvStyrke(int selvStyrke){
    mSelvStyrke = selvStyrke;
}
int Magi::getSelvStyrke() const{
    return mSelvStyrke;
}

void Magi::setManaPrice(int manaPrice){
    mManaPrice = manaPrice;
}
int Magi::getManaPrice() const{
    return mManaPrice;
}

void Magi::setElement(std::string element){
    mElement = element;
}
std::string Magi::getElement() const{
    return mElement;
}
