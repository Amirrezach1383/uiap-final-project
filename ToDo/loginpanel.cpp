#include "loginpanel.h"
#include "ui_loginpanel.h"

LoginPanel::LoginPanel(std::map<QString, Users> users, QWidget *parent) : QMainWindow {parent}
    , user(users)
    , ui(new Ui::LoginPanel) {

    ui->setupUi(this);

    connect(ui->backPB, SIGNAL(clicked()), this, SLOT(backPBClicked()));
    connect(ui->loginPB, SIGNAL(clicked()), this, SLOT(loginPBClicked()));
}

LoginPanel::~LoginPanel() {
    delete ui;
}

void LoginPanel::backPBClicked() {

    MainPanel *panel = new MainPanel(user);
    panel->show();
    this->close();

}
void LoginPanel::loginPBClicked() {
    if(allError() == false) {
        openAndSetMessageBox();
        MainToDoPanel *panel = new MainToDoPanel(ui->usernameLE->text(), user);
        panel->show();
        this->close();
    }
}

void LoginPanel::openAndSetMessageBox () {
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Confirm Data"));
    msgBox.setText(tr("Successfully Login!"));
    QPixmap pixmap(":/Image/Icons/icons8-tick-50.png");
    msgBox.setIconPixmap(pixmap);

    msgBox.exec();
}

// Error Functions
bool LoginPanel::allError() {
    bool error = false;
    if(usernameErrors())
        error = true;
    if(passwordErrors())
        error = true;

    return error;
}
bool LoginPanel::usernameErrors() {
    QString username = ui->usernameLE->text();

    if(username == "") {
        ui->usernameErrorLB->setText("This field is empty");
        return true;
    }

    int i = 0;
    while(i < username.length()) {
        if((username[i] >= 'A' && username[i] <= 'Z') || ((username[i] >= 'a' && username[i] <= 'z')) || (username[i] >= '0' && username[i] <= '9')) {
            i++;
            continue;
        }
        if(username[i] == '.' || username[i] == '_' || username[i] == '-') {
            i++;
            continue;
        }
        ui->usernameErrorLB->setText("Invalid data");
        return true;
    }

    if(username.length() <= 3) {
        ui->usernameErrorLB->setText("Invalid data");
        return true;
    }

    i = 0;
    for(auto it = user.begin(); it != user.end(); it++) {
        if(username == it->first) {
            i++;
        }
    }
    if(i < 1) {
        ui->usernameErrorLB->setText("This username dosen't exists");
        return true;
    }

    return false;
}
bool LoginPanel::passwordErrors() {
    QString username = ui->usernameLE->text();
    QString password = ui->passwordLE->text();

    if(password == "") {
        ui->passwordErrorLB->setText("This field is empty");
        return true;
    }

    int i = 0;
    while(i < password.length()) {
        if((password[i] >= 'A' && password[i] <= 'Z') || ((password[i] >= 'a' && password[i] <= 'z')) || (password[i] >= '0' && password[i] <= '9')) {
            i++;
            continue;
        }
        if(password[i] == '.' || password[i] == '_' || password[i] == '-') {
            i++;
            continue;
        }
        ui->passwordErrorLB->setText("Invalid data");
        return true;
    }

    if(password.length() <= 3) {
        ui->passwordErrorLB->setText("Invalid data");
        return true;
    }

    i = 0;
    for(auto it = user.begin(); it != user.end(); it++) {
        if(username == it->first && password == it->second.getPassword()) {
            i++;
        }
    }
    if(i < 1) {
        ui->passwordErrorLB->setText("Incorrect password");
        return true;
    }

    return false;
}

