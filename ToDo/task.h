#include <QString>
#include <users.h>
#include <ctime>

#ifndef TASK_H
#define TASK_H

class Task {
public:
    Task();

private:
    QString taskTitle;
    QString taskDetails;

    bool favorite;

    Users relatedUser;

    tm taskTime;
};

#endif // TASK_H
