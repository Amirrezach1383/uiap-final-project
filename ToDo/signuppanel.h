#ifndef SIGNUPPANEL_H
#define SIGNUPPANEL_H

#include <QMainWindow>
#include <users.h>
#include <QtSql>
#include <QFileInfo>
#include <mainpanel.h>

namespace Ui {
class SignUpPanel;
}

class SignUpPanel : public QMainWindow
{
    Q_OBJECT

public:
    std::map<QString, Users> user;

    SignUpPanel(std::map<QString, Users> users, QWidget *parent = nullptr);
    ~SignUpPanel();


    // Error Functions
    bool allErrors ();
    bool usernameErrors ();
    bool firstNameErrors ();
    bool lastNameErrors ();
    bool passwordErrors ();
    // // //

    // DataBase Control
    bool conOpen ();
    void conClose ();

private slots:
    void signUpPBClicked();
    void backPBClicked();

private:
    QSqlDatabase toDoDB;
    Ui::SignUpPanel *ui;
};

#endif // SIGNUPPANEL_H
