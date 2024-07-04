#include <QString>
#include <ctime>
#include <QDate>

#ifndef TASK_H
#define TASK_H

class Task {
public:
    Task();

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
