#include "loginpanel.h"
#include "ui_loginpanel.h"

LoginPanel::LoginPanel(QWidget *parent) : QMainWindow {parent}, ui(new Ui::LoginPanel) {
    ui->setupUi(this);
}

LoginPanel::~LoginPanel() {
    delete ui;
}
