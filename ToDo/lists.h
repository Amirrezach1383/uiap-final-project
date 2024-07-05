#include <task.h>
#include <LinkList.h>

#ifndef LISTS_H
#define LISTS_H

class Lists
{
public:
    Lists();

    void setListID (int);
    void setUsername (QString);
    void setTitle (QString);
    void setColor (QString);
    void addTaskList (Task);

private:
    int listID;
    QString username;
    QString title;
    QString color;
    LinkList<Task> taskList;
};

#endif // LISTS_H
