#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>

#include "Hero.h"
#include "Fjende.h"
#include "Controller.h"

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
    //QSqlQuery query;


    int gameStatus{0};          //int til spil-status
    int eventyrStatus{0};       //int til eventyr-status
    int fjende{0};              //int til fjende-valg
    int heroLoad{0};            //int til hero-valg
    std::string heroNavn;       //string til hero-navn
    Hero myHero;               //Hero der spilles med
    Fjende enemy;               //Fjende
    Controller Game(myHero, enemy);
    Game.addEmemies();         //tilføjelse af fjender

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
               myHero = Hero(heroNavn);
               Game.setHero(myHero);
               std::cout << std::endl;
               gameStatus = 3;
               break;
           case 2: //Vælg eksisterende hero
               Game.printHeros();
               std::cout << "Vælg din Hero vha. indeks/id" << std::endl;
               std::cin >> heroLoad;
               Game.loadHero(heroLoad);
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
                   Game.printEnemies();
                   std::cout << "Indtast valg vha. indeks" << std::endl;
                   std::cin >> fjende;
                   std::cout << std::endl;
                   gameStatus = 4;
               }
               else if (eventyrStatus == 2){ //gemmer hero
                   Game.saveHero();
                   gameStatus = 0;
               }
               else if (eventyrStatus == 3){ //lukker spil uden at gemme
                   gameStatus = 0;
               }
               else if (eventyrStatus == 4){ //printer hero stats
                   Game.printHeroStats();
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
               gameStatus = Game.fight(fjende);
                break;
           default:
               std::cout << "Du valgte et ugyldigt tal, prøv igen!" << std::endl;
               std::cout << std::endl;
       }
    }



    return 1;
}
