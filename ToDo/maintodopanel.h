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

private:
    Ui::MainToDoPanel *ui;
};

#endif // MAINTODOPANEL_H
