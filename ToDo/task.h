#include <QString>
#include <ctime>
#include <QDate>

#ifndef TASK_H
#define TASK_H

class Task {
public:
    Task();

    void setTitle (QString);
    void setListID (int);
    void setDetails (QString);
    void setTaskID (int);
    void setCompleted (bool);
    void setFavorite (bool);
    void setAssignedUser (QString);
    void setReminder (QDate);


    QString getTitle ();
    int getListID ();
    QString getDetails ();
    int getTaskID ();
    bool getCompleted ();
    bool getFavorite ();
    QString getAssignedUser ();
    QDate getReminder ();

private:
    QString title;
    QString details;
    int taskID;
    int listID;

    bool completed;
    bool favorite;

    QString assignedUser;

    QDate reminder;
};

#endif // TASK_H
