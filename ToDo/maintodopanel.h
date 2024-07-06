#ifndef MAINTODOPANEL_H
#define MAINTODOPANEL_H

#include <QMainWindow>
#include <mainpanel.h>


namespace Ui {
class MainToDoPanel;
}

class MainToDoPanel : public QMainWindow
{
    Q_OBJECT

public:
    std::map<QString, Users> user;
    QString loginUsername;

    explicit MainToDoPanel(QString, std::map<QString, Users>, QWidget *parent = nullptr);
    ~MainToDoPanel();

    void unCheckedPB ();

private slots:
    void newListPBClicked();
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
