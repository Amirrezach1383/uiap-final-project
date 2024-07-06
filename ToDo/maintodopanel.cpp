#include "maintodopanel.h"
#include "ui_maintodopanel.h"

MainToDoPanel::MainToDoPanel(QString username, std::map<QString, Users> users,QWidget *parent)
    : QMainWindow(parent)
    , user(users)
    , loginUsername(username)
    , ui(new Ui::MainToDoPanel) {
    ui->setupUi(this);

    ui->myDayPB->setChecked(true);
    ui->mainStack->setCurrentIndex(0);
    ui->titleLB->setText("My Day");

    ui->sideTasksMenu->setHidden(true);

    // Connects
    connect(ui->myDayPB, SIGNAL(clicked()), this, SLOT(myDayPBClicked()));
    connect(ui->importantPB, SIGNAL(clicked()), this, SLOT(importantPBClicked()));
    connect(ui->assignedToMePB, SIGNAL(clicked()), this, SLOT(assignedPBClicked()));
    connect(ui->tasksPB, SIGNAL(clicked()), this, SLOT(taskPBClicked()));

    connect(ui->newListPB, SIGNAL(clicked()), this, SLOT(newListPBClicked()));

    connect(ui->myDayNewTaskPB, SIGNAL(clicked()), this, SLOT(myDayNewTaskPBClicked()));
    connect(ui->listsNewTaskPB, SIGNAL(clicked()), this, SLOT(listNewTaskPBClicked()));

    connect(ui->logOutPB, SIGNAL(clicked()), this, SLOT(logOutPBClicked()));


}

MainToDoPanel::~MainToDoPanel()
{
    delete ui;
}

// Private Slots

void MainToDoPanel::newListPBClicked() {
    QVBoxLayout *frameLayout = qobject_cast<QVBoxLayout*>(ui->listsFrame->layout());

    QString buttonText = tr("List %1").arg(frameLayout->count());
    QPushButton *listButton = new QPushButton(buttonText, ui->listsFrame);

    QIcon icon (":/Image/Icons/list_icon.png");
    listButton->setIcon(icon);

    QSize size (20, 20);
    listButton->setIconSize(size);

    listButton->setCheckable(true);
    listButton->setAutoExclusive(true);

    frameLayout->insertWidget(frameLayout->count() - 1, listButton);

    // connect(listButton, SIGNAL(clicked()), this, SLOT(listPb_clicked()));

}

void MainToDoPanel::myDayPBClicked() {
    ui->titleLB->setText("My Day");
    if(ui->myDayPB->isChecked()) {
        ui->mainStack->setCurrentIndex(0);
    }
}
void MainToDoPanel::importantPBClicked() {
    ui->titleLB->setText("Important");
    if(ui->importantPB->isChecked()) {
        ui->mainStack->setCurrentIndex(1);
    }
}
void MainToDoPanel::assignedPBClicked() {
    ui->titleLB->setText("Assigned To Me");
    if(ui->assignedToMePB->isChecked()) {
        ui->mainStack->setCurrentIndex(2);
    }
}
void MainToDoPanel::taskPBClicked() {
    ui->titleLB->setText("Task");
    if(ui->tasksPB->isChecked()) {
        ui->mainStack->setCurrentIndex(3);
    }
}

void MainToDoPanel::listNewTaskPBClicked() {
    if(ui->listsNewTaskPB->isChecked()) {
        ui->sideTasksMenu->setVisible(true);
    } else {
        ui->sideTasksMenu->setHidden(true);
    }
}
void MainToDoPanel::myDayNewTaskPBClicked() {
    if(ui->myDayNewTaskPB->isChecked()) {
        ui->sideTasksMenu->setVisible(true);
    } else {
        ui->sideTasksMenu->setHidden(true);
    }

}

void MainToDoPanel::logOutPBClicked() {
    MainPanel *panel = new MainPanel(user);
    panel->show();
    this->close();
}
// // // //
