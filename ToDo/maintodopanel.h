#ifndef MAINTODOPANEL_H
#define MAINTODOPANEL_H

#include <QMainWindow>
#include <mainpanel.h>
#include <QPushButton>
#include <QMessageBox>


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

    explicit MainToDoPanel(QString, std::map<QString, Users>, QWidget *parent = nullptr);
    ~MainToDoPanel();

    void unCheckedPB ();

    void setUsersInfoInPanel ();

    void setUsersListInfo ();
    void addUsersListPB (Lists&);

    void setUsersTasksInfo ();
    void setUsersMyDayInfo ();
    void setUsersAssignedInfo ();

    void setListsTaskInfo (Lists&);
    void addListsTaskItems(Task);

    void addNewListToUsersList (Lists&);

    void setListsBackGround (Color);

    void addNewTaskItem (Task&);
    void addNewTaskInfo (Task&);

    // Error Functions
    bool allErrors ();

    bool taskTitleError ();
    bool assignToOtherError ();
    // // //

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

private:
    Ui::MainToDoPanel *ui;
};

#endif // MAINTODOPANEL_H
