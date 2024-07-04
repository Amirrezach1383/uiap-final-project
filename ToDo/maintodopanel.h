#ifndef MAINTODOPANEL_H
#define MAINTODOPANEL_H

#include <QMainWindow>

namespace Ui {
class MainToDoPanel;
}

class MainToDoPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainToDoPanel(QWidget *parent = nullptr);
    ~MainToDoPanel();

    void unCheckedPB ();

private slots:
    void on_newListPB_clicked();

    void on_myDayPB_clicked();

    void on_importantPB_clicked();

    void on_assignedToMePB_clicked();

    void on_tasksPB_clicked();

    void on_listsButton_0_clicked();

    void on_newTaskPB_myDay_clicked();

    void listPb_clicked();

    void on_newTaskPB_Task_clicked();

    void on_newTaskPB_list_clicked();

private:
    Ui::MainToDoPanel *ui;
};

#endif // MAINTODOPANEL_H
