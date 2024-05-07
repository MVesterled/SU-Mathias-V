#include "Controller.h"
#include <iostream>

Controller::Controller(Hero hero, Fjende fjende)
{
    mHero = hero;
    mFjende = fjende;

    //Laver database Game hvis den ikke findes
    QString createDatabaseQuery = "CREATE DATABASE IF NOT EXISTS Game";
    mQuery.exec(createDatabaseQuery);

    //Laver tabel til heros (unik nøgle til navnet)
    QString createTableQuery1 = "CREATE TABLE IF NOT EXISTS hero ("
                                "id INT AUTO_INCREMENT PRIMARY KEY,"
                                "level INT,"
                                "styrke INT,"
                                "xp INT,"
                                "hp INT,"
                                "name VARCHAR(255) UNIQUE,"
                                "gold INT"
                                ")";
    mQuery.exec(createTableQuery1);

    QString dropFkKey = "ALTER TABLE enemies DROP FOREIGN KEY enemies_ibfk_1; ";
    mQuery.exec(dropFkKey);

    //Laver tabel til grotter
    QString createTableQuery2 =    "DROP TABLE IF EXISTS grotter; "
                                   "CREATE TABLE grotter ("
                                   "grotte_id INT PRIMARY KEY AUTO_INCREMENT,"
                                   "name VARCHAR(255),"
                                   "gold INT"
                                   ")";
    mQuery.exec(createTableQuery2);

    //Laver tabel til enemies
    QString createTableQuery3 = "DROP TABLE IF EXISTS enemies; "
                                   "CREATE TABLE enemies ("
                                   "id INT AUTO_INCREMENT PRIMARY KEY,"
                                   "name VARCHAR(255),"
                                   "xp_gain INT,"
                                   "hp INT,"
                                   "styrke INT,"
                                   "grotte_id INT,"
                                   "FOREIGN KEY(grotte_id) REFERENCES grotter(grotte_id)"
                                   ")";
    mQuery.exec(createTableQuery3);

    //Laver tabel til magier
    QString createTableQuery4 = "DROP TABLE IF EXISTS magier; "
                                   "CREATE TABLE magier ("
                                   "magi_id INT AUTO_INCREMENT PRIMARY KEY,"
                                   "name VARCHAR(255),"
                                   "styrke INT,"
                                   "selv_styrke INT,"
                                   "mana_pris INT,"
                                   "element VARCHAR(255),"
                                   "guld_pris INT,"
                                   "magi_krav INT"
                                   ")";
    mQuery.exec(createTableQuery4);

    //Liste af grotter laves
    QList<QVariantList> grotter = {
            {"Garden dungeon (easy)", 500},
            {"Mystery dungeon (Medium)", 1500},
            {"The abyssal dungeon (Hard)", 4000}};


       //SQL statement forberedes
        mQuery.prepare("INSERT INTO grotter (name, gold) VALUES (:name, :gold)");

        // Ranged based for loop der sætter ind i tabel
        for (const QVariantList grotte : grotter) {
            mQuery.bindValue(":name", grotte[0]);
            mQuery.bindValue(":gold", grotte[1]);
            mQuery.exec();
        }
}

void Controller::waitForEnter() {
    std::cout << "Tryk 'enter' for at slås";
    std::cin.ignore();
    std::cin.get();    // venter på tryk
}

//Funktion der printer heroes
void Controller::printHeros(){
    std::cout << "Heroes:" << std::endl;
        mQuery.exec("SELECT * FROM hero"); // Hero er tabel.
        qDebug() << "Antal heros:" << mQuery.size(); //printer antal tasks

        //Printer
        while (mQuery.next()) {
            int id = mQuery.value(0).toInt();
            int level = mQuery.value(1).toInt();
            int styrke = mQuery.value(2).toInt();
            int xp = mQuery.value(3).toInt();
            int hp = mQuery.value(4).toInt();
            QString name = mQuery.value(5).toString();
            int gold = mQuery.value(6).toInt();


            qDebug() << "Id:" << id << "Navn:" << name << "Level:" << level << "Styrke:" << styrke << "XP:" << xp
                     << "HP:" << hp << "Gold:" << gold;
        }
}

//Funktion der gemmer hero
void Controller::saveHero(){
    mQuery.prepare("INSERT INTO hero (level, styrke, xp, hp, name, gold) "
                   "VALUES (:level, :styrke, :xp, :hp, :name, :gold) "
                   "ON DUPLICATE KEY UPDATE "
                   "level = :level, "
                   "styrke = :styrke, "
                   "xp = :xp, "
                   "hp = :hp,"
                   "gold = :gold");

    // Sætter værdier
    mQuery.bindValue(":level", mHero.getLevel()); // Example level value
    mQuery.bindValue(":styrke", mHero.getDamage()); // Example styrke value
    mQuery.bindValue(":xp", mHero.getXp()); // Example xp value
    mQuery.bindValue(":hp", mHero.getHp()); // Example hp value
    mQuery.bindValue(":name", QString::fromStdString(mHero.getName())); // Example name value
    mQuery.bindValue(":gold", mHero.getGold());
    mQuery.exec();

}

void Controller::printHeroStats(){
    std::cout << "Hero navn: " << mHero.getName() << " Styrke: " << mHero.getDamage() << " Level: "
              << mHero.getLevel() << " HP: " << mHero.getHp() << " XP: "
              << mHero.getXp() << " Gold: " << mHero.getGold() << std::endl;
    std::cout << "Magier:" << std::endl;
    for (int i = 0; i < mHero.getMagi().size(); ++i){
        std::cout << "MagiID: " << mHero.getMagi()[i].getID() << " " << "Navn: " << mHero.getMagi()[i].getName() << " " <<
                     "Styrke: " << mHero.getMagi()[i].getStyrke() << " " << "SelvStyrke: " << mHero.getMagi()[i].getSelvStyrke() << " " <<
                     "ManaPris: " << mHero.getMagi()[i].getManaPrice() << " " << "Element: " << mHero.getMagi()[i].getElement() << std::endl;
    }
}

//Funktion der loader hero
void Controller::loadHero(int heroNumber){
    //Select der skal returnere alt data på given fjende
    mQuery.prepare("SELECT level, styrke, xp, hp, name, gold FROM hero WHERE id = :heroNumber;");
    mQuery.bindValue(":heroNumber", heroNumber); //Binder id
    mQuery.exec(); //Kører query

    //assigner værdier
    if (mQuery.next()) {
            int level = mQuery.value("level").toInt();
            QString name = mQuery.value("name").toString();
            int xp = mQuery.value("xp").toInt();
            int hp = mQuery.value("hp").toInt();
            int styrke = mQuery.value("styrke").toInt();
            int gold = mQuery.value("gold").toInt();

            std::string nameTemp = name.toStdString();
            mHero.setName(nameTemp);
            mHero.setXp(xp);
            mHero.setHp(hp);
            mHero.setDamage(styrke);
            mHero.setLevel(level);
            mHero.setGold(gold);

        }
}

//Funktion der printer enemies
void Controller::printEnemies(){
    std::cout << "Fjender:" << std::endl;
        mQuery.exec("SELECT * FROM enemies"); // Hero er tabel.
        qDebug() << "Antal fjender:" << mQuery.size(); //printer antal tasks

        //Printer
        while (mQuery.next()) {
            int id = mQuery.value(0).toInt();
            QString name = mQuery.value(1).toString();
            int xpGain = mQuery.value(2).toInt();
            int hp = mQuery.value(3).toInt();
            int styrke = mQuery.value(4).toInt();



            qDebug() << "Id:" << id << "Navn:" << name << "Styrke:" << styrke << "XP_Gain:" << xpGain << "HP:" << hp;
        }
}

//Indsætter fjenderne i database
void Controller::addEmemies(){
    //Liste af enemies laves
    QList<QVariantList> enemies = {
            {"Cat", 100, 2, 1, 1},
            {"Child", 200, 4, 1, 1},
            {"Small Goblin", 300, 5, 1, 1},
            {"Medium Goblin", 400, 7, 1, 2},
            {"Cow", 500, 8, 2, 2},
            {"Wizard", 700, 20, 3, 2},
            {"Giant", 1200, 20, 4, 3},
            {"Dragon", 3000, 50, 8, 3},
            {"Fire-Dragon", 5000, 80, 10, 3}};

       //SQL statement forberedes
        mQuery.prepare("INSERT INTO enemies (name, xp_gain, hp, styrke, grotte_id) VALUES (:name, :xp_gain, :hp, :styrke, :grotte_id)");

        // Ranged based for loop der sætter ind i tabel
        for (const auto& enemy : enemies) {
            mQuery.bindValue(":name", enemy[0]);
            mQuery.bindValue(":xp_gain", enemy[1]);
            mQuery.bindValue(":hp", enemy[2]);
            mQuery.bindValue(":styrke", enemy[3]);
            mQuery.bindValue(":grotte_id", enemy[4]);
            mQuery.exec();
        }

}

//funktion der håndterer en kamp mellem fjende og hero
int Controller::fight(int enemyNumber){
    mFjende.setEnemyStats(enemyNumber);
    //så længe en karekter er i live kan de slås:
    while (mHero.isAlive() && mFjende.isAlive()){
        std::cout << "Hero: " << mHero.getName() << " har hp: " << mHero.getHp() << std::endl;
        std::cout << "Fjende: " << mFjende.getName() << " har hp: " << mFjende.getHp() << std::endl;
        waitForEnter();
        mFjende.takeDamage(mHero.getDamage());
        //Tjek om Hero har vundet
        if (!mFjende.isAlive()){ //hvis enemy dør
            std::cout << "Du vandt kampen!" << std::endl << std::endl;
            mHero.resetAfterFight();
            mHero.addXp((mFjende.getXpGain()));
            return 3;
        }
        mHero.takeDamage(mFjende.getDamage());
        if (!mHero.isAlive()){ //hvis hero dør
            std::cout << "Du tabte..." << std::endl << std::endl;
            mHero.resetAfterFight();
            return 99;
    }
}
    return -1;
}

//printer mulige grotter
void Controller::printGrotter(){
    std::cout << "Grotter:" << std::endl;
        mQuery.exec("SELECT * FROM grotter"); // grotter er tabel.
        qDebug() << "Antal Grotter:" << mQuery.size(); //printer antal tasks

        //Printer
        while (mQuery.next()) {
            int id = mQuery.value(0).toInt();
            QString name = mQuery.value(1).toString();
            int gold = mQuery.value(2).toInt();

            qDebug() << "Id:" << id << "Navn:" << name << "Gold:" << gold;
        }
}

//funktion der håndterer en grottekørsel (3 monstre)
int Controller::fightCave(int caveNumber){
    mGrotte.loadGrotteData(caveNumber);
    mGrotte.loadGrotteFjender(caveNumber);
    std::cout << "Du har valgt grotten: " << mGrotte.getName() << std::endl;
    std::cout << "Dine modstandere består af: " << mGrotte.getFjende(0).getName() << ", " << mGrotte.getFjende(1).getName()
                                                << " og " << mGrotte.getFjende(2).getName() << std::endl;
    std::cout << "Første kamp imod: " << mGrotte.getFjende(0).getName() << " starter nu!" << std::endl;
    if (Controller::fight(caveNumber*3-2) == 3)
    std::cout << "Anden kamp imod: " << mGrotte.getFjende(1).getName() << " starter nu!" << std::endl;
    else {return 3;}
    if (Controller::fight(caveNumber*3-2+1) == 3)
    std::cout << "Tredje kamp imod: " << mGrotte.getFjende(2).getName() << " starter nu!" << std::endl;
    else {return 3;}
    if (Controller::fight(caveNumber*3-2+2) != 3)
    return 3;

    mHero.adjustGold(mGrotte.getGold());
    std::cout << "Du har gennemført grotten!!! " << mGrotte.getGold() << " Gold-coins er tilføjet til din hero" << std::endl;
    return 3;
}

void Controller::setHero(Hero hero){
    mHero = hero;
}

//tilføjelser af magier til databasen
void Controller::addMagier(){
    // Liste af magi laves
    QList<QVariantList> magier = {
        {"FireStrike", 4, 2, 2, "ild", 750, 0},
        {"FireWave", 6, 2, 3, "ild", 500, 1},
        {"FireBlast", 9, 3, 4, "ild", 1000, 2},
        {"EarthStrike", 4, 2, 2, "Earth", 750, 0},
        {"EarthWave", 6, 2, 3, "Earth", 500, 4},
        {"EarthBlast", 9, 3, 4, "Earth", 1000, 5},
        {"WaterStrike", 4, 2, 2, "Water", 750, 0},
        {"WaterWave", 6, 2, 3, "Water", 500, 7},
        {"WaterBlast", 9, 3, 4, "Water", 1000, 8},
        {"RegenHP", 0, -5, 2, "Metal", 750, 0},
        {"Sword", 6, 2, 3, "Metal", 500, 0},
        {"Whip", 9, 3, 4, "Metal", 1000, 11},
        {"RegenMana", 0, 0, -5, "Wood", 750, 0},
        {"RootAttack", 6, 2, 3, "Wood", 500, 0},
        {"StealHP", 4, -4, 2, "Wood", 1000, 0}
    };

    // SQL statement forberedes
    mQuery.prepare("INSERT INTO magier (name, styrke, selv_styrke, mana_pris, element, guld_pris, magi_krav) "
                       "VALUES (:name, :styrke, :selv_styrke, :mana_pris, :element, :guld_pris, :magi_krav)");

    for (const QVariantList& magi : magier) {
        mQuery.bindValue(":name", magi[0]);
        mQuery.bindValue(":styrke", magi[1]);
        mQuery.bindValue(":selv_styrke", magi[2]);
        mQuery.bindValue(":mana_pris", magi[3]);
        mQuery.bindValue(":element", magi[4]);
        mQuery.bindValue(":guld_pris", magi[5]);
        mQuery.bindValue(":magi_krav", magi[6]);

        if (!mQuery.exec()) {
            qDebug() << "Fejl under udførelse af INSERT forespørgsel:" << mQuery.lastError().text();
        }
    }
}

void Controller::magishop(){
    std::cout << "Butikken består af:" << std::endl;
        mQuery.exec("SELECT * FROM magier"); // grotter er tabel.
        qDebug() << "Antal Produkter:" << mQuery.size(); //printer antal tasks

        //Printer
        while (mQuery.next()) {
            int id = mQuery.value(0).toInt();
            QString name = mQuery.value(1).toString();
            int styrke = mQuery.value(2).toInt();
            int selv_styrke = mQuery.value(3).toInt();
            int mana_pris = mQuery.value(4).toInt();
            QString element = mQuery.value(5).toString();
            int guld_pris = mQuery.value(6).toInt();
            int magi_krav = mQuery.value(7).toInt();

            qDebug() << "Id:" << id << "Navn:" << name << "Styrke:" << styrke << "Selv_skade:" << selv_styrke
                     << "Mana_Pris:" << mana_pris << "Element:" << element << "Guld_pris:" << guld_pris << "Magi_krav:" << magi_krav;
        }

        int magivalg{0};
        std::cout << "Indtast valg vha. indeks eller 0 for at returnere" << std::endl;
        std::cin >> magivalg;

        if (mHero.buyMagic(magivalg) == 0){
             std::cout << "Du havde ikke guld nok... Du føres tilbage til menu" << std::endl;
        }
        else {
            std::cout << "Magi tilhøjet til: " << mHero.getName() << std::endl;
        }


}
