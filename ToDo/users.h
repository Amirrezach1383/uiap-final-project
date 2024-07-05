#include <QString>
#include <lists.h>
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
    std::list<Lists> taskLists;


};

#endif // USERS_H
