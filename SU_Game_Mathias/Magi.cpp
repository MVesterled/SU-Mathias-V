#include "Magi.h"

Magi::Magi(int id)
{
    //Select der skal returnere alt data på given magi
    mQuery.prepare("SELECT magi_id, name, styrke, selv_styrke, mana_pris, element FROM magier WHERE magi_id = :id;");
    mQuery.bindValue(":id", id); //Binder id
    mQuery.exec(); //Kører query

    //assigner værdier
    if (mQuery.next()) {
            int id = mQuery.value("magi_id").toInt();
            QString name = mQuery.value("name").toString();
            int styrke = mQuery.value("styrke").toInt();
            int selv_styrke = mQuery.value("selv_styrke").toInt();
            int mana_pris = mQuery.value("mana_pris").toInt();
            QString element = mQuery.value("element").toString();

            mID = id;
            mName = name.toStdString();
            mStyrke = styrke;
            mSelvStyrke = selv_styrke;
            mManaPrice = mana_pris;
            mElement = element.toStdString();
        }
}

void Magi::setID(int id){
    mID = id;
}
int Magi::getID() const{
    return mID;
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

void Magi::setName(std::string name){
    mName = name;
}
std::string Magi::getName() const{
    return mName;
}
