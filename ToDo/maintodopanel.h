#ifndef MAINTODOPANEL_H
#define MAINTODOPANEL_H

#include "qboxlayout.h"
#include <QMainWindow>
#include <mainpanel.h>
#include <QPushButton>
#include <QMessageBox>
#include <QtWidgets>
#include <QPrinter>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class MainToDoPanel;
}

class MainToDoPanel : public QMainWindow
{
    Q_OBJECT

public:
    std::map<QString, Users> user;
    QString loginUsername;

    QHash <QPushButton*, Lists> listButtonMap;
    QHash <QPushButton*, Task> taskButtonMap;
    QHash <QWidget*, QHBoxLayout*> layoutMap;
    QHash <QPushButton*, QString> detailsMap;

    explicit MainToDoPanel(QString, std::map<QString, Users>, QWidget *parent = nullptr);
    ~MainToDoPanel();

    void unCheckedPB ();

    void setUsersInfoInPanel ();

    void setUsersListInfo ();
    void addUsersListPB (Lists&);

    void setUsersTasksInfo ();
    void setUsersMyDayInfo ();
    void setUsersAssignedInfo ();
    void setUsersImportantInfo ();

    void setListsTaskInfo (Lists&);
    void addListsTaskItems(Task);

    void addNewListToUsersList (Lists&);

    void setListsBackGround (Color);

    void addNewTaskItem (Task&);
    void addNewTaskInfo (Task&);
    void addNewTaskToUserLists (Task&);

    void updateListBackground (Color c);

    // Error Functions
    bool allErrors ();

    bool taskTitleError ();
    bool assignToOtherError ();
    // // //

    void cleanStack ();

    void cleanSideTaskMenu ();

    void addWidgetToScrollArea (QVBoxLayout*, Task);

    void unCheckedListButton ();

    void checkReminder ();

    // void addListToDB (Lists&);
    // void addTaskToDB (Task&);

    // bool openDB(QSqlDatabase&);
    // void closeDB(QSqlDatabase&);

    void setComboBox (Lists &);

private slots:
    void newListPBClicked();
    void listButtonClicked();

    void taskCompletePBClicked();

    void listNewTaskPBClicked();

    void myDayPBClicked();
    void importantPBClicked();
    void assignedPBClicked();
    void taskPBClicked();

    void logOutPBClicked();

    void addTaskPBClicked();

    void showTaskDetails();

    void comboBoxChanged();

    void getPDFOutPut ();
private:
    Ui::MainToDoPanel *ui;
};

#endif // MAINTODOPANEL_H
