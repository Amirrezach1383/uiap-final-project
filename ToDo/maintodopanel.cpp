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
    Lists newList;
    QVBoxLayout *frameLayout = qobject_cast<QVBoxLayout*>(ui->listsFrame->layout());

    QString buttonText = tr("List %1").arg(frameLayout->count());
    QPushButton *listButton = new QPushButton(buttonText, ui->listsFrame);

    newList.setTitle(buttonText);

    QIcon icon (":/Image/Icons/list_icon.png");
    listButton->setIcon(icon);

    QSize size (20, 20);
    listButton->setIconSize(size);

    listButton->setCheckable(true);
    listButton->setAutoExclusive(true);

    frameLayout->insertWidget(frameLayout->count() - 1, listButton);

    listButtonMap.insert(listButton, newList);
    addNewListToUsersList(newList);

    connect(listButton, SIGNAL(clicked()), this, SLOT(listButtonClicked()));
}
void MainToDoPanel::listButtonClicked() {
    QPushButton* listButton = qobject_cast<QPushButton*>(sender());
    Lists selectedList = listButtonMap[listButton];
    setListsTaskInfo(selectedList);

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


// Set Info Functions
void MainToDoPanel::setUsersInfoInPanel () {

    ui->userInfoLB->setText(loginUsername);

    setUsersListInfo();
    setUsersAssignedInfo();
    setUsersTasksInfo();
    setUsersMyDayInfo();
}

void MainToDoPanel::setUsersListInfo () {

    Users userTmp = user[loginUsername];

    std::list<Lists> listTmp = userTmp.getLists();

    for(auto it = listTmp.begin(); it != userTmp.getLists().end(); it++) {
        addUsersListPB(*it);
    }

}
void MainToDoPanel::addUsersListPB (Lists& list) {
    QVBoxLayout *frameLayout = qobject_cast<QVBoxLayout*>(ui->listsFrame->layout());

    QString buttonText = list.getTile();
    QPushButton *listButton = new QPushButton(buttonText, ui->listsFrame);

    QIcon icon (":/Image/Icons/list_icon.png");
    listButton->setIcon(icon);

    QSize size (20, 20);
    listButton->setIconSize(size);

    listButton->setCheckable(true);
    listButton->setAutoExclusive(true);

    frameLayout->insertWidget(frameLayout->count() - 1, listButton);

    listButtonMap.insert(listButton, list);

    connect(listButton, SIGNAL(clicked()), this, SLOT(listButtonClicked()));
}


void MainToDoPanel::setUsersTasksInfo () {
    Users userTmp = user[loginUsername];

}
void MainToDoPanel::setUsersMyDayInfo () {
    Users userTmp = user[loginUsername];

}
void MainToDoPanel::setUsersAssignedInfo () {
    Users userTmp = user[loginUsername];

}

void MainToDoPanel::setListsTaskInfo (Lists& selectedList) {

    LinkList<Task> tmpTask = selectedList.getTask();
    Node<Task> *tmp = tmpTask.getHeadNode();

    while(tmp) {
        addListsTaskItems(tmp->getData());
        tmp = tmp->getNextNode();
    }
}
void MainToDoPanel::addListsTaskItems(Task task) {
    QVBoxLayout *frameLayout = qobject_cast<QVBoxLayout*>(ui->listsScrollAFrame->layout());

    QHBoxLayout *itemLayout = new QHBoxLayout;
    QString labelTitle = task.getTitle();

    QLabel *taskLabel = new QLabel(labelTitle);


    QPushButton* completePB = new QPushButton("", ui->listsScrollAFrame);

    QIcon icon (":/Image/Icons/out_line_circle.png");
    completePB->setIcon(icon);

    QSize size(20, 20);
    completePB->setIconSize(size);

    completePB->setCheckable(true);
    completePB->setAutoExclusive(true);

    completePB->icon().addFile(":/Image/Icons/fill_circle.png", size, QIcon::Normal, QIcon::On);

    if(task.getCompleted()) {
        completePB->setChecked(true);
    } else {
        completePB->setChecked(false);
    }

    itemLayout->insertWidget(0, taskLabel);
    itemLayout->insertWidget(0, completePB);

    itemLayout->setContentsMargins(10, 1, 20, 0);
    itemLayout->setSpacing(0);

    frameLayout->insertLayout(0, itemLayout);

    taskButtonMap.insert(completePB, task);

    // connect ()
}

// Add functions

void MainToDoPanel::addNewListToUsersList (Lists& newList) {

    Users userTmp = user[loginUsername];

    userTmp.addToLists(newList);

    user[loginUsername] = userTmp;
}
