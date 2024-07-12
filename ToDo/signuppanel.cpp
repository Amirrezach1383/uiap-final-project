#include "signuppanel.h"
#include "ui_signuppanel.h"
#include <QMessageBox>


SignUpPanel::SignUpPanel(std::map<QString, Users> users, QWidget *parent)
    : QMainWindow {parent}
    , user(users)
    , ui(new Ui::SignUpPanel){
    ui->setupUi(this);

    this->setWindowTitle("Sign Up");

    QIcon icon (":/Image/Icons/icons8-to-do-48.png");
    this->setWindowIcon(icon);

    connect(ui->signUpPB, SIGNAL(clicked()), this, SLOT(signUpPBClicked()));
    connect(ui->backPB, SIGNAL(clicked()), this, SLOT(backPBClicked()));

    connect(ui->visiblePB, SIGNAL(clicked()), this, SLOT(changeVisible()));

    ui->passwordLE->setEchoMode(QLineEdit::Password);
}

SignUpPanel::~SignUpPanel() {
    delete ui;
}

void SignUpPanel::changeVisible () {
    if(ui->visiblePB->isChecked()) {
        ui->passwordLE->setEchoMode(QLineEdit::Normal);
    } else {
        ui->passwordLE->setEchoMode(QLineEdit::Password);
    }
}

// Error Functions

bool SignUpPanel::allErrors() {

    bool error = false;

    if (usernameErrors())
        error = true;

    if (lastNameErrors())
        error = true;

    if (firstNameErrors())
        error = true;

    if(passwordErrors())
        error = true;

    return error;
}

bool SignUpPanel::usernameErrors () {
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
    for(auto &it : user) {
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
    for(auto &it : user) {
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

// // //


// Private Slots
void SignUpPanel::signUpPBClicked() {

    if(allErrors() == false) {

        Users tmp;
        getAndSetData(tmp);
        setDataINDB(tmp);
    }
}

void SignUpPanel::backPBClicked() {
    MainPanel *panel = new MainPanel(user);
    panel->show();
    this->close();
}

// // // //

void SignUpPanel::getAndSetData(Users &user_tmp) {

    QString username = ui->usernameLE->text();
    QString lastName = ui->lastNameLE->text();
    QString firstName = ui->firstNameLE->text();
    QString password = ui->passwordLE->text();

    user_tmp.setUsername(username);
    user_tmp.setLastName(lastName);
    user_tmp.setFirstName(firstName);
    user_tmp.setPassword(password);

    user[username] = user_tmp;

}
void SignUpPanel::setDataINDB(Users &usertmp) {
    if(openDB()) {
        QSqlQuery qry;
        qry.prepare("INSERT INTO Users (Username, Password, FirstName, LastName) VALUES ('"+usertmp.getUsername()+"', '"+usertmp.getPassword()+"', '"+usertmp.getFirstName()+"', '"+usertmp.getLastName()+"')");

        if (qry.exec()) {

            openAndSetMessageBox();
            closeDB();

            MainPanel *panel = new MainPanel(user);
            panel->show();
            this->close();
        } else {
            QMessageBox::critical(this, tr("Error"), qry.lastError().text());
        }
    }
}

void SignUpPanel::openAndSetMessageBox() {
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Confirm Data"));
    msgBox.setText(tr("Successfully registered !"));

    QPixmap pixmap(":/Image/Icons/icons8-tick-50.png");
    msgBox.setIconPixmap(pixmap);

    msgBox.exec();
}

// DataBase Control
void SignUpPanel::closeDB() {
    toDoDB.close();
    toDoDB.removeDatabase(QSqlDatabase::defaultConnection);
}
bool SignUpPanel::openDB() {
    toDoDB = QSqlDatabase::addDatabase("QSQLITE");
    toDoDB.setDatabaseName("E:/Final Project/uiap-final-project-Amirrezach1383/ToDo/To_Do_DB.db");

    if(toDoDB.open())
        return true;
    return false;
}

