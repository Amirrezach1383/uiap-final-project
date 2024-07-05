#include <QString>
#include <lists.h>
#include <list>

#ifndef USERS_H
#define USERS_H

class Users {
public:
    Users();

    void setUsername (QString);
    void setPassword (QString);
    void setFirstName (QString);
    void setLastName (QString);

    QString getUsername ();
    QString getPassword ();
    QString getFirstName ();
    QString getLastName ();

    std::list<Lists> taskLists;
private:
    QString username;
    QString password;
    QString firstName;
    QString lastName;



};

#endif // USERS_H
