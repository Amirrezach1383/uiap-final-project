#include <QString>
#include <users.h>

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
};

#endif // TASK_H
