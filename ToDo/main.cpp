#include "mainpanel.h"
#include <QApplication>
#include <QtSql>

bool readDataFromDB (QSqlDatabase, std::map<QString,Users>);
bool openDB(QSqlDatabase);
void closeDB(QSqlDatabase);

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainPanel w(*new std::map <QString, Users>);
    w.show();

    return a.exec();
}
bool readDataFromDB (QSqlDatabase &toDoDB, std::map<QString,Users> user) {

    return true;
}
bool openDB(QSqlDatabase &toDoDB) {
    toDoDB = QSqlDatabase::addDatabase("QSQLITE");
    toDoDB.setDatabaseName("E:/Final Project/uiap-final-project-Amirrezach1383/ToDo/To_Do_DB.db");

    if(toDoDB.open())
        return true;
    return false;
}
void closeDB(QSqlDatabase &toDoDB) {
    toDoDB.close();
    toDoDB.removeDatabase(QSqlDatabase::defaultConnection);
}

