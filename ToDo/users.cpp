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
void Users::addToLists (Lists& d) {
    d.setListID(lists.size() + (username.toInt() % 20));
    d.setUsername(this->username);
    lists.push_back(d);
}
void Users::setLists(int listID, Lists &list) {

    for(auto it = lists.begin(); it != lists.end(); it++) {
        if(it->getListID() == listID) {
            *it = list;
            break;
        }
    }
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
    return Lists();
}

std::list<Lists> Users::getLists() {
    return lists;
}
