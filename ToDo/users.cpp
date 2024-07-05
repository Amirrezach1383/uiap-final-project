#include "users.h"

Users::Users() {}


void Users::setUsername (QString d) {
    username = d;
}
void Users::setPassword (QString d) {
    password = d;
}
void Users::setFirstName (QString d) {
    firstName = d;
}
void Users::setLastName (QString d) {
    lastName = d;
}
void Users::addToLists (Lists d) {
    lists.push_back(d);
}


QString Users::getUsername () {
    return username;
}
QString Users::getPassword () {
    return password;
}
QString Users::getFirstName () {
    return firstName;
}
QString Users::getLastName () {
    return lastName;
}
Lists Users::getLists(int listID) {
    for(auto it = lists.begin(); it != lists.end(); it++) {
        if(it->getListID() == listID)
            return *it;
    }
    return *new Lists;
}
