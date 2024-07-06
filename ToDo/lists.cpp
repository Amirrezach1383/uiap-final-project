#include "lists.h"

Lists::Lists() : title("Untitled List") {}

void Lists::setListID (int d) {
    listID = d;
}
void Lists::setUsername (QString d) {
    username = d;
}
void Lists::setTitle (QString d) {
    title = d;
}
void Lists::setColor (Color d) {
    color = d;
}
void Lists::addTask (Task d) {
    d.setTaskID(taskList.getSize() + 1);
    d.setListID(listID);
    taskList << d;
}
void Lists::setTask(int taskID, Task task) {
    Node<Task>* tmp = taskList.getHeadNode();

    while(tmp){
        if(tmp->getData().getTaskID() == taskID) {
            tmp->setData(task);
        }
    }
}

QString Lists::getUsername () {
    return username;
}
QString Lists::getTile () {
    return title;
}
Color Lists::getColor (){
    return color;
}
int Lists::getListID (){
    return listID;
}
Task Lists::getTask (int taskID) {
    Node<Task> *tmp = taskList.getHeadNode();

    while(tmp) {
        if(tmp->getData().getTaskID() == taskID)
            return tmp->getData();
        tmp = tmp->getNextNode();
    }
    return Task();
}
LinkList<Task> Lists::getTask() {
    return taskList;
}
