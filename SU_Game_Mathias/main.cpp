#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>

#include "Hero.h"
#include "Fjende.h"

//Funktion der skal vente på enter tryk
void waitForEnter() {
    std::cout << "Tryk 'enter' for at slås";
    std::cin.ignore();
    std::cin.get();    // venter på tryk
}

int main(int argc, char *argv[])
{
    //SQL forbindelse:
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Game"); //Databasenavn
    db.setUserName("sammy");  // brugernavn
    db.setPassword("password");  // kode
    db.open();
    QSqlQuery query;

    //Laver database Game hvis den ikke findes
    QString createDatabaseQuery = "CREATE DATABASE IF NOT EXISTS Game";
    query.exec(createDatabaseQuery);

    //Laver tabel til heros (unik nøgle til navnet)
    QString createTableQuery1 = "CREATE TABLE IF NOT EXISTS hero ("
                                "id INT AUTO_INCREMENT PRIMARY KEY,"
                                "level INT,"
                                "styrke INT,"
                                "xp INT,"
                                "hp INT,"
                                "name VARCHAR(255) UNIQUE"
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
    int gameStatus{0};          //int til spil-status
    int eventyrStatus{0};       //int til eventyr-status
    int fjende{0};              //int til fjende-valg
    int heroLoad{0};            //int til hero-valg
    std::string heroNavn;       //string til hero-navn
    Hero newHero;               //Hero der spilles med
    Hero hData;                 //dummy hero
    Fjende fData;               //dummy fjende
    fData.addEmemies();         //tilføjelse af fjender

    while (true){

    switch (gameStatus) {
            case 0: //Hovedmenu
                std::cout << "--- HOVED MENU ---" << std::endl;
                std::cout << "Muligheder:" << std::endl;
                std::cout << "(1) Start nyt eventyr" << std::endl;
                std::cout << "(2) Load eksisterende eventyr" << std::endl;
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
               std::cin >> heroLoad;
               newHero.loadHero(heroLoad);
               std::cout << std::endl;
               gameStatus = 3;
               break;
           case 3: //Klar til kamp eller luk spil?
               std::cout << "Muligheder:" << std::endl;
               std::cout << "(1) Vis fjender du kan slås med" << std::endl;
               std::cout << "(2) Luk eventyr og GEM Hero" << std::endl;
               std::cout << "(3) Luk eventyr uden at gemme" << std::endl;
               std::cout << "(4) Vis Hero-stats" << std::endl;

               std::cin >> eventyrStatus;
               std::cout << std::endl;

               if (eventyrStatus == 1){
                   fData.printEnemies();
                   std::cout << "Indtast valg vha. indeks" << std::endl;
                   std::cin >> fjende;
                   std::cout << std::endl;
                   gameStatus = 4;
               }
               else if (eventyrStatus == 2){ //gemmer hero
                   newHero.saveHero();
                   gameStatus = 0;
               }
               else if (eventyrStatus == 3){ //lukker spil uden at gemme
                   gameStatus = 0;
               }
               else if (eventyrStatus == 4){ //printer hero stats
                   newHero.printHeroStats();
                   gameStatus = 3;
               }
               else {
                   std::cout << "Forkert valg, prøv igen" << std::endl;
                   std::cin >> eventyrStatus;
               }
               std::cout << std::endl;
               break;
           case 4: //Slåskamp
                std::cout << "FIGHT!" << std::endl;
                fData.setEnemyStats(fjende);
                //så længe en karekter er i live kan de slås:
                while (newHero.isAlive() && fData.isAlive()){
                    std::cout << "Hero: " << newHero.getName() << " har hp: " << newHero.getHp() << std::endl;
                    std::cout << "Fjende: " << fData.getName() << " har hp: " << fData.getHp() << std::endl;
                    waitForEnter();
                    fData.takeDamage(newHero.getDamage());
                    newHero.takeDamage(fData.getDamage());
                    if (!newHero.isAlive()){ //hvis hero dør
                        std::cout << "Du tabte..." << std::endl << std::endl;
                        newHero.resetAfterFight();
                        gameStatus = 3;
                        break;}
                    else if(!fData.isAlive()){ //hvis enemy dør
                        std::cout << "Du vandt kampen!" << std::endl << std::endl;
                        newHero.resetAfterFight();
                        newHero.addXp((fData.getXpGain()));
                        gameStatus = 3;
                        break;
                    }
                }
        break;
           default:
               std::cout << "Du valgte et ugyldigt tal, prøv igen!" << std::endl;
               std::cout << std::endl;
       }
    }




    return 1;
}
