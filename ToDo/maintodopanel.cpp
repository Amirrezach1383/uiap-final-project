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

    connect(ui->listsNewTaskPB, SIGNAL(clicked()), this, SLOT(listNewTaskPBClicked()));

    connect(ui->addTaskPB, SIGNAL(clicked()), this, SLOT(addTaskPBClicked()));

    connect(ui->logOutPB, SIGNAL(clicked()), this, SLOT(logOutPBClicked()));
}

MainToDoPanel::~MainToDoPanel()
{
    delete ui;
}

void MainToDoPanel::unCheckedPB() {

    ui->myDayPB->setChecked(false);
    ui->assignedToMePB->setChecked(false);
    ui->tasksPB->setChecked(false);
    ui->importantPB->setChecked(false);
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

    unCheckedPB();

    ui->mainStack->setCurrentIndex(ui->mainStack->indexOf(ui->Lists));
    ui->titleLB->setText(listButton->text());

    Lists selectedList = listButtonMap[listButton];

    Color c = selectedList.getColor();
    setListsBackGround(c);

    ui->listsBKG->setStyleSheet("");
    setListsTaskInfo(selectedList);

}

void MainToDoPanel::taskCompletePBClicked() {

    QIcon circleOutLine (":/Image/Icons/out_line_circle.png");
    QIcon circleFill (":/Image/Icons/fill_circle.png");

    QPushButton *completeTask = qobject_cast<QPushButton*>(sender());


    if(completeTask->isChecked()) {
        completeTask->setIcon(circleFill);
    }
    else {
        completeTask->setIcon(circleOutLine);
    }



    Users userTmp = user[loginUsername];
    Task taskTmp = taskButtonMap[completeTask];

    int listID = taskTmp.getListID();
    Lists tmpList = userTmp.getLists(listID);

    if(completeTask->isChecked()) {
        taskTmp.setCompleted(true);
    } else {
        taskTmp.setCompleted(false);
    }

    tmpList.setTask(taskTmp.getTaskID(), taskTmp);
    userTmp.setLists(listID, tmpList);
    user[loginUsername] = userTmp;

    taskButtonMap[completeTask] = taskTmp;
}

/// Fixed Menu Buttons

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

/// /// ///

void MainToDoPanel::listNewTaskPBClicked () {
    if(ui->listsNewTaskPB->isChecked()) {
        ui->sideTasksMenu->setVisible(true);
    } else {
        ui->sideTasksMenu->setHidden(true);
    }
}

void MainToDoPanel::addTaskPBClicked () {
    if(!allErrors()) {
        Task tmpTask;
        addNewTaskInfo(tmpTask);
        addNewTaskItem(tmpTask);

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

void MainToDoPanel::setListsBackGround(Color c) {

    if(c == Blue) {
        ui->listsBKG->setStyleSheet(
        "QWidget {"
            "background-color: rgb(66, 56, 246);"
            "border-radius : 5px;"
                "}"
            );

    }
    if(c == Red) {
        ui->listsBKG->setStyleSheet(
            "QWidget {"
            "background-color:  rgb(113, 54, 38);"
            "border-radius : 5px;"
            "}"
            );
    }
    if(c == Green) {
        ui->listsBKG->setStyleSheet(
            "QWidget {"
            "background-color: rgb(12, 119, 18 );"
            "border-radius : 5px;"
            "}"
            );
    }
    if(c == Yellow) {
        ui->listsBKG->setStyleSheet(
            "QWidget {"
            "background-color: rgb(212, 178, 2);"
            "border-radius : 5px;"
            "}"
            );
    }
    if(c == Black) {
        ui->listsBKG->setStyleSheet(
            "QWidget {"
            "background-color: rgb(18, 13, 13);"
            "border-radius : 5px;"
            "}"
            );
    }
    if(c == Default) {
        ui->listsBKG->setStyleSheet(
            "QWidget {"
            "background-color: rgb(33, 33, 33);"
            "border-radius : 5px;"
            "}"
            );
    }
}

// Add functions

void MainToDoPanel::addNewListToUsersList (Lists& newList) {

    Users userTmp = user[loginUsername];
    userTmp.addToLists(newList);
    user[loginUsername] = userTmp;
}
void MainToDoPanel::addNewTaskItem (Task& task) {

    QVBoxLayout *frameLayout = qobject_cast<QVBoxLayout*>(ui->listsScrollAFrame->layout());
    QWidget *widget = new QWidget;

    widget->setStyleSheet(
        "QWidget {"
        "background-color: rgb(50, 50, 50);"
        "border-radius : 5px;"
        "}"
        );

    QHBoxLayout *itemLayout = new QHBoxLayout;
    QString labelTitle = ui->taskNameLE->text();

    QLabel *taskLabel = new QLabel(labelTitle);

    QPushButton* completePB = new QPushButton("", ui->listsScrollAFrame);
    QPushButton* star = new QPushButton("", ui->listsScrollAFrame);

    QIcon starFillIcon (":/Image/Icons/fill_star_color.png");
    QIcon starOutLineIcon (":/Image/Icons/out_line_star.png");

    if(task.getFavorite())
        star->setIcon(starFillIcon);
    if(!task.getFavorite())
        star->setIcon(starOutLineIcon);

    QIcon circleOutLine (":/Image/Icons/out_line_circle.png");
    QIcon circleFill (":/Image/Icons/fill_circle.png");
    completePB->setIcon(circleOutLine);

    QSize size(20, 20);
    completePB->setIconSize(size);

    completePB->setCheckable(true);

    if(task.getCompleted()) {
        completePB->setChecked(true);
        completePB->setIcon(circleFill);
    }
    else {
        completePB->setChecked(false);
        completePB->setIcon(circleOutLine);
    }

    completePB->setChecked(true);

    itemLayout->insertWidget(0, star);
    itemLayout->insertWidget(1, taskLabel);
    itemLayout->insertWidget(2, completePB);

    itemLayout->setContentsMargins(10, 1, 20, 0);
    itemLayout->setSpacing(0);

    widget->setLayout(itemLayout);

    frameLayout->insertWidget(0, widget);

    taskButtonMap.insert(completePB, task);

    connect(completePB, SIGNAL(clicked()), this, SLOT(taskCompletePBClicked()));

}

/// //// //// /// // Add date After
void MainToDoPanel::addNewTaskInfo (Task& task) {
    task.setTitle(ui->taskNameLE->text());
    task.setDetails(ui->detailsTE->toPlainText());
    task.setAssignedUser(ui->assignToOtherLE->text());
    task.setFavorite(ui->favPB->isChecked());
    task.setCompleted(ui->completePBSideMenu->isChecked());

}
/////////////
void MainToDoPanel::addListsTaskItems(Task task) {
    QVBoxLayout *frameLayout = qobject_cast<QVBoxLayout*>(ui->listsScrollAFrame->layout());

    QHBoxLayout *itemLayout = new QHBoxLayout;
    QString labelTitle = task.getTitle();

    QLabel *taskLabel = new QLabel(labelTitle);


    QPushButton* completePB = new QPushButton("", ui->listsScrollAFrame);
    QPushButton* star = new QPushButton("", ui->listsScrollAFrame);

    QIcon starFillIcon (":/Image/Icons/fill_star_color.png");
    QIcon starOutLineIcon (":/Image/Icons/out_line_star.png");

    if(task.getFavorite())
        star->setIcon(starFillIcon);
    if(!task.getFavorite())
        star->setIcon(starOutLineIcon);

    QIcon icon (":/Image/Icons/out_line_circle.png");
    completePB->setIcon(icon);

    QSize size(20, 20);
    completePB->setIconSize(size);

    completePB->setCheckable(true);

    completePB->icon().addFile(":/Image/Icons/fill_circle.png", size, QIcon::Normal, QIcon::On);

    if(task.getCompleted()) {
        completePB->setChecked(true);
    } else {
        completePB->setChecked(false);
    }

    itemLayout->insertWidget(0, star);
    itemLayout->insertWidget(1, taskLabel);
    itemLayout->insertWidget(2, completePB);

    itemLayout->setContentsMargins(10, 1, 20, 0);
    itemLayout->setSpacing(0);

    frameLayout->insertLayout(0, itemLayout);

    taskButtonMap.insert(completePB, task);

    connect(completePB, SIGNAL(clicked()), this, SLOT(taskCompletePBClicked()));
}


// Error Functions
bool MainToDoPanel::allErrors () {
    if(taskTitleError())
        return true;
    if(assignToOtherError())
        return true;

    return false;
}

bool MainToDoPanel::taskTitleError () {
    if(ui->taskNameLE->text() == "") {
        QMessageBox errorMessage;
        errorMessage.setText(tr("Please fill task title"));
        errorMessage.setWindowTitle(tr("Fill Error"));
        errorMessage.exec();
        return true;
    }
    return false;
}
bool MainToDoPanel::assignToOtherError () {
    QString assignedUsername = ui->assignToOtherLE->text();

    if(assignedUsername == "")
        return false;

    if(user.find(assignedUsername)->first != "")
        return false;

    QMessageBox errorMessage;
    errorMessage.setText(tr("This user doesen't exsit"));
    errorMessage.setWindowTitle(tr("Find Error"));
    errorMessage.exec();
    return true;

}

