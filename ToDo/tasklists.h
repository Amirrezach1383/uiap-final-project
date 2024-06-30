#include <task.h>
#include <LinkList.h>

#ifndef TASKLISTS_H
#define TASKLISTS_H

class TaskLists
{
public:
    TaskLists();
private:
    QString listName;
    LinkList<Task> listTask;
};

#endif // TASKLISTS_H
