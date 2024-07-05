#include "mainpanel.h"
#include "ui_mainpanel.h"
#include <users.h>

MainPanel::MainPanel(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainPanel) {
    ui->setupUi(this);

    connect(ui->signinPB, SIGNAL(clicked()), this, SLOT(signinPBClicked()));
    connect(ui->signinPB, SIGNAL(clicked()), this, SLOT(logininPBClicked()));
}

MainPanel::~MainPanel() {
    delete ui;
}

void MainPanel::signinPBClicked() {



}

void MainPanel::loginPBClicked() {

}

