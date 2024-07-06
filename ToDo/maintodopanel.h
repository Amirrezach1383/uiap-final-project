#ifndef MAINTODOPANEL_H
#define MAINTODOPANEL_H

#include <QMainWindow>
#include <mainpanel.h>
#include <QPushButton>


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
    void setListsTaskInfo ();


private slots:
    void newListPBClicked();
    void listButtonClicked();

    void listNewTaskPBClicked();
    void myDayNewTaskPBClicked();

    void myDayPBClicked();
    void importantPBClicked();
    void assignedPBClicked();
     void taskPBClicked();

    void logOutPBClicked();

private:
    Ui::MainToDoPanel *ui;
};

#endif // MAINTODOPANEL_H
