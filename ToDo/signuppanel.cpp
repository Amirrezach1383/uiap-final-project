#include "signuppanel.h"
#include "ui_signuppanel.h"

SignUpPanel::SignUpPanel(QWidget *parent) : QMainWindow {parent} ,ui(new Ui::SignUpPanel){
    ui->setupUi(this);
}

SignUpPanel::~SignUpPanel() {
    delete ui;
}
