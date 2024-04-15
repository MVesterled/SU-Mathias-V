#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>

#include "Hero.h"

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("robot_worker");
    db.setUserName("sammy");  // Change to username
    db.setPassword("password");  // Change to password
    db.open();

    QSqlQuery query;

    qDebug() << query.exec("SELECT * FROM task"); // employee er her navnet på en tabel, ikke et schema

    qDebug() << "Number of rows:" << query.size();

    qDebug() << "Finished";

    std::cout << "say what" << std::endl;

    Hero r;

    return 1;
}
