#include "mainpanel.h"
#include "ui_mainpanel.h"
#include <users.h>
#include <loginpanel.h>
#include <signuppanel.h>

MainPanel::MainPanel(std::map<QString, Users> users, QWidget *parent) : QMainWindow(parent)
    , user(users)
    , ui(new Ui::MainPanel) {

    ui->setupUi(this);

    connect(ui->signinPB, SIGNAL(clicked()), this, SLOT(signinPBClicked()));
    connect(ui->loginPB, SIGNAL(clicked()), this, SLOT(loginPBClicked()));
}

MainPanel::~MainPanel() {
    delete ui;
}

void MainPanel::signinPBClicked() {

    SignUpPanel *panel = new SignUpPanel(user);
    this->close();
    panel->show();
}

void MainPanel::loginPBClicked() {

    LoginPanel *panel = new LoginPanel (user);
    this->close();
    panel->show();
}

