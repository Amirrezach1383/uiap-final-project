#include "maintodopanel.h"
#include "ui_maintodopanel.h"

MainToDoPanel::MainToDoPanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainToDoPanel)
{
    ui->setupUi(this);
}

MainToDoPanel::~MainToDoPanel()
{
    delete ui;
}
