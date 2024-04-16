#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>

#include "Hero.h"
#include "Fjende.h"

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Game");
    db.setUserName("sammy");  // Change to username
    db.setPassword("password");  // Change to password
    db.open();
    QSqlQuery query;

    //Laver database Game hvis den ikke findes
    QString createDatabaseQuery = "CREATE DATABASE IF NOT EXISTS Game";
    query.exec(createDatabaseQuery);

    //Laver tabel til heros
    QString createTableQuery1 = "CREATE TABLE IF NOT EXISTS hero ("
                                "id INT AUTO_INCREMENT PRIMARY KEY,"
                                "level INT,"
                                "styrke INT,"
                                "xp INT,"
                                "hp INT,"
                                "name VARCHAR(255)"
                                ")";
    query.exec(createTableQuery1);

    //Laver tabel til enemies
    QString createTableQuery2 = "DROP TABLE IF EXISTS enemies; "
                                   "CREATE TABLE enemies ("
                                   "id INT AUTO_INCREMENT PRIMARY KEY,"
                                   "name VARCHAR(255),"
                                   "xp_gain INT,"
                                   "hp INT,"
                                   "styrke INT"
                                   ")";
    query.exec(createTableQuery2);
    int gameStatus{0};
    int eventyrStatus{0};
    std::string heroNavn;
    Hero newHero;
    Hero hData;
    Fjende fData;
    fData.addEmemies();

    while (true){

    switch (gameStatus) {
            case 0: //Hovedmenu
                std::cout << "--- HOVED MENU ---" << std::endl;
                std::cout << "Muligheder:" << std::endl;
                std::cout << "(1) Start nyt eventyr" << std::endl;
                std::cout << "(2) Load eksisterende eventyr" << std::endl;
                std::cout << "(3) Vis fjender" << std::endl;
                std::cout << "Indtast valg vha. indeks" << std::endl;
                std::cin >> gameStatus;
                std::cout << std::endl;
                break;
           case 1: //Opret ny hero
               std::cout << "Vælg hvad din Hero skal hedde:" << std::endl;
               std::cin >> heroNavn;
               newHero = Hero(heroNavn);
               std::cout << std::endl;
               gameStatus = 3;
               break;
           case 2: //Vælg eksisterende hero
               hData.printHeros();
               std::cout << "Vælg din Hero vha. indeks/id" << std::endl;
               std::cout << std::endl;
               gameStatus = 0;
               break;
           case 3: //Klar til kamp eller luk spil?
               std::cout << "(1) Vis fjender du kan slås med" << std::endl;
               std::cout << "(2) Luk eventyr og GEM Hero" << std::endl;
               std::cout << "(3) Luk eventyr uden at gemme" << std::endl;
               std::cin >> eventyrStatus;

               if (eventyrStatus == 1){
                   fData.printEnemies();
                   gameStatus = 4;
               }
               else if (eventyrStatus == 2){
                   newHero.saveHero();
                   gameStatus = 0;
               }
               else if (eventyrStatus == 3){
                   gameStatus = 0;
               }
               else {
                   std::cout << "Forkert valg, prøv igen" << std::endl;
                   std::cin >> eventyrStatus;
               }
               std::cout << std::endl;
               break;
           case 4: //Slåskamp
                std::cout << "Valg 4" << std::endl;
                gameStatus = 0;
        break;
           default:
               std::cout << "Du valgte et ugyldigt tal, prøv igen!" << std::endl;
               std::cout << std::endl;
       }
    }




    return 1;
}
