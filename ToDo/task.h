#include <QString>
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

    QString relatedUserUsername;

    tm taskTime;
};

#endif // TASK_H
