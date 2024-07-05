#ifndef SIGNUPPANEL_H
#define SIGNUPPANEL_H

#include <QMainWindow>
#include <users.h>

namespace Ui {
class SignUpPanel;
}

class SignUpPanel : public QMainWindow
{
    Q_OBJECT

public:
    SignUpPanel(std::map<QString, Users> users, QWidget *parent = nullptr);
    ~SignUpPanel();

    bool allErrors ();
    bool usernameErrors ();
    bool firstNameErrors ();
    bool lastNameErrors ();
    bool passwordErrors ();

    std::map<QString, Users> user;

private slots:
    void signUpPBClicked();

private:
    Ui::SignUpPanel *ui;
};

#endif // SIGNUPPANEL_H
