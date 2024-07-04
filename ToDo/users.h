#include <QString>
#include <tasklists.h>
#include <map>
#include <list>

#ifndef USERS_H
#define USERS_H

class Users {
public:
    Users();
private:
    QString username;
    QString password;
    QString firstName;
    QString lastName;
    std::list<TaskLists> usertaskLists;

    std::map <QString, Users> usersMap;
};

#endif // USERS_H
