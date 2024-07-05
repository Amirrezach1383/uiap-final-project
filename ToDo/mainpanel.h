#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QMainWindow>
#include <users.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainPanel;
}
QT_END_NAMESPACE

class MainPanel : public QMainWindow
{
    Q_OBJECT

public:
    MainPanel(std::map<QString, Users> users, QWidget *parent = nullptr);
    ~MainPanel();

    std::map<QString, Users> user;
private slots:
    void signinPBClicked();
    void loginPBClicked();


private:
    Ui::MainPanel *ui;
};
#endif // MAINPANEL_H
