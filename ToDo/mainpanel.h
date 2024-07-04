#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainPanel;
}
QT_END_NAMESPACE

class MainPanel : public QMainWindow
{
    Q_OBJECT

public:
    MainPanel(QWidget *parent = nullptr);
    ~MainPanel();


private slots:
    void on_signinPB_clicked();
    void on_loginPB_clicked();


private:
    Ui::MainPanel *ui;
};
#endif // MAINPANEL_H
