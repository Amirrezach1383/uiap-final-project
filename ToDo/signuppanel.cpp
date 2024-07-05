#include "signuppanel.h"
#include "ui_signuppanel.h"


SignUpPanel::SignUpPanel(std::map<QString, Users> users, QWidget *parent)
    : QMainWindow {parent}
    , user(users)
    , ui(new Ui::SignUpPanel){
    ui->setupUi(this);

    connect(ui->signUpPB, SIGNAL(clicked()), this, SLOT(signUpPBClicked()));
}

SignUpPanel::~SignUpPanel() {
    delete ui;
}

bool SignUpPanel::allErrors() {
    if (usernameErrors())
        return true;

    if (lastNameErrors())
        return true;

    if (firstNameErrors())
        return true;

    if(passwordErrors())
        return true;

    return false;
}

bool SignUpPanel::usernameErrors () {
    QString username = ui->usernameLE->text();

    if(username == "") {
        ui->usernameErrorLB->setText("This field is empty");
        return true;
    }

    int i = 0;
    while(i < username.length()) {
        if((username[i] >= 'A' && username[i] <= 'Z') || ((username[i] >= 'a' && username[i] <= 'z'))) {
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
    for(auto it : user) {
        if(username == it.first) {
            i++;
        }
    }
    if(i > 1) {
        ui->usernameErrorLB->setText("This username already exists");
        return true;
    }

    return false;
}
bool SignUpPanel::firstNameErrors () {
    QString firstName = ui->firstNameLE->text();

    if(firstName == "") {
        ui->firstNameErrorLB->setText("This field is empty");
        return true;
    }

    int i = 0;
    while(i < firstName.length()) {
        if((firstName[i] >= 'A' && firstName[i] <= 'Z') || ((firstName[i] >= 'a' && firstName[i] <= 'z'))) {
            i++;
            continue;
        }
        ui->firstNameErrorLB->setText("Invalid data");
        return true;
    }

    if(firstName.length() <= 2) {
        ui->firstNameErrorLB->setText("Invalid data");
        return true;
    }

    ui->firstNameErrorLB->clear();
    return false;
}
bool SignUpPanel::lastNameErrors () {
    QString lastName = ui->lastNameLE->text();

    if(lastName == "") {
        ui->lastNameErrorLB->setText("This field is empty");
        return true;
    }

    int i = 0;
    while(i < lastName.length()) {
        if((lastName[i] >= 'A' && lastName[i] <= 'Z') || ((lastName[i] >= 'a' && lastName[i] <= 'z'))) {
            i++;
            continue;
        }
        ui->lastNameErrorLB->setText("Invalid data");
        return true;
    }

    if(lastName.length() <= 2) {
        ui->lastNameErrorLB->setText("Invalid data");
        return true;
    }

    ui->lastNameErrorLB->clear();
    return false;
}
bool SignUpPanel::passwordErrors () {
    QString password = ui->passwordLE->text();

    if(password == "") {
        ui->passwordErrorLB->setText("This field is empty");
        return true;
    }

    int i = 0;
    while(i < password.length()) {
        if((password[i] >= 'A' && password[i] <= 'Z') || ((password[i] >= 'a' && password[i] <= 'z'))) {
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
    for(auto it : user) {
        if(password == it.first) {
            i++;
        }
    }
    if(i > 1) {
        ui->passwordErrorLB->setText("This password already exists");
        return true;
    }

    return false;
}

void SignUpPanel::signUpPBClicked() {

    if(allErrors() == false) {
        QString username = ui->usernameLE->text();
        QString lastName = ui->lastNameLE->text();
        QString firstName = ui->firstNameLE->text();
        QString password = ui->passwordLE->text();

        Users user_tmp;
        user_tmp.setUsername(username);
        user_tmp.setLastName(lastName);
        user_tmp.setFirstName(firstName);
        user_tmp.setPassword(password);

        user[username] = user_tmp;
    }
}


