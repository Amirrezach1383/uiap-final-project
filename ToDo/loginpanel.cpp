#include "loginpanel.h"
#include "ui_loginpanel.h"

LoginPanel::LoginPanel(std::map<QString, Users> users, QWidget *parent) : QMainWindow {parent}
    , user(users)
    , ui(new Ui::LoginPanel) {

    ui->setupUi(this);
}

LoginPanel::~LoginPanel() {
    delete ui;
}
