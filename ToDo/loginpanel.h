#ifndef LOGINPANEL_H
#define LOGINPANEL_H

#include <QMainWindow>
#include <users.h>
#include <mainpanel.h>
#include <QMessageBox>
#include <maintodopanel.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginPanel;
}
QT_END_NAMESPACE

class LoginPanel : public QMainWindow
{
    Q_OBJECT
private slots:
    void loginPBClicked ();
    void backPBClicked ();


public:
    std::map<QString, Users> user;

    LoginPanel(std::map<QString, Users>, QWidget *parent = nullptr);
    ~LoginPanel();

    // Errors Functions
    bool allError();
    bool usernameErrors ();
    bool passwordErrors ();

    void openAndSetMessageBox ();


private:
    Ui::LoginPanel *ui;
};

#endif // LOGINPANEL_H
