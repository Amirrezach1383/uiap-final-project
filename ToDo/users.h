#include <QString>
#include <lists.h>

#ifndef USERS_H
#define USERS_H

class Users {
public:
    Users();

    void setUsername (QString);
    void setPassword (QString);
    void setFirstName (QString);
    void setLastName (QString);
    void addToLists (Lists);

    QString getUsername ();
    QString getPassword ();
    QString getFirstName ();
    QString getLastName ();
    Lists getLists(int);

private:
    QString username;
    QString password;
    QString firstName;
    QString lastName;
    std::list<Lists> lists;



};

#endif // USERS_H
