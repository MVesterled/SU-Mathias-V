#ifndef MAGI_H
#define MAGI_H
#include <string>

class Magi
{
public:
    Magi();

    void setStyrke(int styrke);
    int getStyrke() const;

    void setSelvStyrke(int selvStyrke);
    int getSelvStyrke() const;

    void setManaPrice(int manaPrice);
    int getManaPrice() const;

    void setElement(std::string element);
    std::string getElement() const;

private:
    int mStyrke, mSelvStyrke, mManaPrice;
    std::string mElement;


};

#endif // MAGI_H
