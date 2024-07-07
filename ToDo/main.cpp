#include "mainpanel.h"
#include "maintodopanel.h"
#include <QApplication>
#include <QtSql>

void readDataFromDB (QSqlDatabase&, std::map<QString,Users>&, std::vector<Task>&, std::vector<Lists>&);
void setTask (std::vector<Task>&);
void setList (std::vector<Lists>&, std::vector<Task>&);
void setUser (std::map<QString, Users>&, std::vector<Lists>&);

bool openDB(QSqlDatabase&);
void closeDB(QSqlDatabase&);

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QSqlDatabase toDoDB;

    std::map<QString, Users> user;
    std::vector<Task> task;
    std::vector<Lists> lists;


    if(openDB(toDoDB)) {
        readDataFromDB(toDoDB, user, task, lists);
    } else
        return 0;

    // MainPanel w(user);
    MainToDoPanel w(*new QString, user);
    w.show();

    return a.exec();
}

void readDataFromDB (QSqlDatabase &toDoDB, std::map<QString,Users> &user, std::vector<Task>& task, std::vector<Lists>& lists) {

    setTask(task);
    setList(lists, task);
    setUser(user, lists);

    closeDB(toDoDB);
}

void setList (std::vector<Lists>& lists, std::vector<Task> &task) {
    QSqlQuery qry("SELECT * FROM Lists");

    while(qry.next()){

        QString title = qry.value("Title").toString();
        QString username = qry.value("Username").toString();
        int listID = qry.value("ListID").toInt();
        Color color = static_cast<Color>(qry.value("Color").toInt());

        Lists tmpList;

        tmpList.setListID(listID);
        tmpList.setColor(color);
        tmpList.setTitle(title);
        tmpList.setUsername(username);

        for(auto it = task.begin(); it != task.end(); it++) {
            if(it->getListID() == listID) {
                tmpList.addTask(*it);
            }
        }

        lists.push_back(tmpList);
    }
}
void setTask (std::vector<Task>& task) {

    QSqlQuery qry("SELECT * FROM Task");

    while(qry.next()) {

        QString title = qry.value("Title").toString();
        QString details = qry.value("Details").toString();
        bool favorite = qry.value("Favorite").toInt();
        bool completed = qry.value("Completed").toInt();
        QString assigned = qry.value("Assigned").toString();
        QString reminder = qry.value("Reminder").toString();
        int listID = qry.value("List ID").toInt();
        int taskID = qry.value("TaskID").toInt();

        Task tmpTask;

        tmpTask.setTaskID(taskID);
        tmpTask.setListID(listID);
        tmpTask.setReminder(QDate::fromString(reminder, Qt::ISODate));
        tmpTask.setAssignedUser(assigned);
        tmpTask.setCompleted(completed);
        tmpTask.setFavorite(favorite);
        tmpTask.setDetails(details);
        tmpTask.setTitle(title);

        task.push_back(tmpTask);

    }

}
void setUser (std::map<QString, Users>& user, std::vector<Lists>& lists) {
      QSqlQuery qry("SELECT * FROM Users");

    while(qry.next()) {

        QString username = qry.value("Username").toString();
        QString password = qry.value("Password").toString();
        QString firstName = qry.value("FirstName").toString();
        QString lastName = qry.value("LastName").toString();

        Users usertmp;
        usertmp.setFirstName(firstName);
        usertmp.setPassword(password);
        usertmp.setUsername(username);
        usertmp.setLastName(lastName);

        for(auto it = lists.begin(); it != lists.end(); it++) {
            if(it->getUsername() == username)
                usertmp.addToLists(*it);
        }

        user[username] = usertmp;
    }

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

