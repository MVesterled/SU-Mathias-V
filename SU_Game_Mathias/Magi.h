#ifndef MAGI_H
#define MAGI_H
#include <string>
#include <QtSql>
#include <QSqlDatabase>

class Magi
{
public:
    Magi(int id);

    void setID(int id);
    int getID() const;

    void setStyrke(int styrke);
    int getStyrke() const;

    void setSelvStyrke(int selvStyrke);
    int getSelvStyrke() const;

    void setManaPrice(int manaPrice);
    int getManaPrice() const;

    void setElement(std::string element);
    std::string getElement() const;

    void setName(std::string name);
    std::string getName() const;

private:
    int mID, mStyrke, mSelvStyrke, mManaPrice;
    std::string mElement, mName;
    QSqlQuery mQuery;

};

#endif // MAGI_H
