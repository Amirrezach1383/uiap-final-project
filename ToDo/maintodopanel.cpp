#include "maintodopanel.h"
#include "ui_maintodopanel.h"

MainToDoPanel::MainToDoPanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainToDoPanel) {
    ui->setupUi(this);

    ui->myDayPB->setChecked(true);
    ui->titleLB->setText("My Day");

    ui->sideTasksMenu->setHidden(true);

}

MainToDoPanel::~MainToDoPanel()
{
    delete ui;
}

void MainToDoPanel::on_newListPB_clicked() {
    QVBoxLayout *frameLayout = qobject_cast<QVBoxLayout*>(ui->listsFrame->layout());

    QString buttonText = tr(" Untitled List %1").arg(frameLayout->count() - 1);
    QPushButton *listButton = new QPushButton(buttonText, ui->listsFrame);
    listButton->icon().addFile(":/Image/Icons/list_icon.png");

    QIcon icon (":/Image/Icons/list_icon.png");
    listButton->setIcon(icon);

    QSize size (25, 25);
    listButton->setIconSize(size);

    listButton->setCheckable(true);
    listButton->setAutoExclusive(true);

    frameLayout->insertWidget(frameLayout->count() - 1, listButton);
}

void MainToDoPanel::on_myDayPB_clicked() {
    ui->titleLB->setText("My Day");
    ui->mainStack->setCurrentIndex(0);

}


void MainToDoPanel::on_importantPB_clicked() {
    ui->titleLB->setText("Important");
    ui->mainStack->setCurrentIndex(1);

}

void MainToDoPanel::on_assignedToMePB_clicked() {
    ui->titleLB->setText("Assigned to me");
    ui->mainStack->setCurrentIndex(2);

}


void MainToDoPanel::on_tasksPB_clicked() {
    ui->titleLB->setText("Tasks");
    ui->mainStack->setCurrentIndex(3);
}


void MainToDoPanel::on_listsButton_0_clicked() {
    ui->titleLB->setText(ui->listsButton_0->text());
    ui->mainStack->setCurrentIndex(4);
}


void MainToDoPanel::on_newTaskPB_myDay_clicked() {

    if(ui->newTaskPB_myDay->isChecked()) {
        ui->sideTasksMenu->setVisible(true);
    } else
        ui->sideTasksMenu->setHidden(true);


}

