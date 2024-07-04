#include <task.h>
#include <LinkList.h>

#ifndef LISTS_H
#define LISTS_H

class Lists
{
public:
    Lists();
private:
    int listID;
    QString username;
    QString title;
    QString color;
    LinkList<Task> listTask;
};

#endif // LISTS_H
