#include "task.h"

Task::Task() : title("Untitled"),
               details("Enter some details"),
               completed(false),
    favorite(false) {}

void Task::setTitle (QString d) {
    title = d;
}
void Task::setListID (int d) {
    listID = d;
}
void Task::setDetails (QString d) {
    details = d;
}
void Task::setTaskID (int d) {
    taskID = d;
}
void Task::setCompleted (bool d) {
    completed = d;
}
void Task::setFavorite (bool d) {
    favorite = d;
}
void Task::setAssignedUser (QString d) {
    assignedUser = d;
}
void Task::setReminder (QDate d) {
    reminder = d;
}


QString Task::getTitle () {
    return title;
}
int Task::getListID () {
    return listID;
}
QString Task::getDetails () {
    return details;
}
int Task::getTaskID () {
    return taskID;
}
bool Task::getCompleted () {
    return completed;
}
bool Task::getFavorite () {
    return favorite;
}
QString Task::getAssignedUser () {
    return assignedUser;
}
QDate Task::getReminder () {
    return reminder;
}

