#include <task.h>
#include <LinkList.h>

#ifndef LISTS_H
#define LISTS_H

enum Color {
    Default, Blue, Red, Green, Yellow, Black
};

class Lists
{
public:
    Lists();

    void setListID (int);
    void setUsername (QString);
    void setTitle (QString);
    void setColor (Color);
    void addTask (Task&);
    void setTask (int, Task);

    QString getUsername ();
    QString getTile ();
    Color getColor ();
    int getListID ();
    Task getTask (int);
    LinkList<Task> getTask();

private:
    int listID;
    QString username;
    QString title;
    Color color;
    LinkList<Task> taskList;
};

#endif // LISTS_H
