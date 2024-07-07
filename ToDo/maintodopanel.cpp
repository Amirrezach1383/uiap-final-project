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

    connect(ui->colorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChanged()));

    // // // // // // // // //
    connect(ui->PDFPB, SIGNAL(clicked()), this, SLOT(getPDFOutPut()));
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

void MainToDoPanel::unCheckedListButton() {
    ui->sideTasksMenu->setHidden(true);
    for(auto it = listButtonMap.begin(); it != listButtonMap.end(); ++it) {
        if(it.key()->isChecked()) {
            it.key()->setChecked(false);
        }
    }
}
// Private Slots

void MainToDoPanel::newListPBClicked() {
    Lists newList;
    QVBoxLayout *frameLayout = qobject_cast<QVBoxLayout*>(ui->listsFrame->layout());

    QString buttonText = tr("List %1").arg(frameLayout->count());
    QPushButton *listButton = new QPushButton(buttonText, ui->listsFrame);

    ui->listsBKG->setStyleSheet("");

    newList.setTitle(buttonText);

    QIcon icon (":/Image/Icons/list_icon.png");
    listButton->setIcon(icon);

    QSize size (20, 20);
    listButton->setIconSize(size);

    listButton->setCheckable(true);
    listButton->setAutoExclusive(true);

    frameLayout->insertWidget(frameLayout->count() - 1, listButton);

    addNewListToUsersList(newList);
    listButtonMap.insert(listButton, newList);

    connect(listButton, SIGNAL(clicked()), this, SLOT(listButtonClicked()));
}
void MainToDoPanel::listButtonClicked() {
    QPushButton* listButton = qobject_cast<QPushButton*>(sender());

    cleanStack();

    unCheckedPB();

    ui->mainStack->setCurrentIndex(ui->mainStack->indexOf(ui->Lists));
    ui->titleLB->setText(listButton->text());

    Lists selectedList = listButtonMap[listButton];

    Color c = selectedList.getColor();
    setListsBackGround(c);

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
        unCheckedListButton ();
        ui->mainStack->setCurrentIndex(0);
    }

    setUsersMyDayInfo();
}
void MainToDoPanel::importantPBClicked() {
    ui->titleLB->setText("Important");
    if(ui->importantPB->isChecked()) {
        unCheckedListButton ();
        ui->mainStack->setCurrentIndex(1);
    }
}
void MainToDoPanel::assignedPBClicked() {
    ui->titleLB->setText("Assigned To Me");
    if(ui->assignedToMePB->isChecked()) {
        unCheckedListButton ();
        ui->mainStack->setCurrentIndex(2);
    }
}
void MainToDoPanel::taskPBClicked() {
    ui->titleLB->setText("Task");
    if(ui->tasksPB->isChecked()) {
        unCheckedListButton ();
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
        addNewTaskToUserLists(tmpTask);
        addNewTaskItem(tmpTask);
        cleanSideTaskMenu();
    }
}

void MainToDoPanel::showTaskDetails() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString details = detailsMap[button];

    if(details == "")
        return;

    QMessageBox msgBox;
    msgBox.setText(details);
    msgBox.setWindowTitle(tr("Task Details"));
    msgBox.exec();

}

void MainToDoPanel::comboBoxChanged() {
    Color c;

    if(ui->colorComboBox->currentText() == "Blue") {
        c = Blue;
        setListsBackGround(c);
        updateListBackground(c);
        return;
    }
    if(ui->colorComboBox->currentText() == "Red") {
        c = Red;
        setListsBackGround(c);
        updateListBackground(c);
        return;
    }
    if(ui->colorComboBox->currentText() == "Black") {
        c = Black;
        setListsBackGround(c);
        updateListBackground(c);
        return;
    }
    if(ui->colorComboBox->currentText() == "Green") {
        c = Green;
        setListsBackGround(c);
        updateListBackground(c);
        return;
    }
    if(ui->colorComboBox->currentText() == "Default") {
        c = Default;
        setListsBackGround(c);
        updateListBackground(c);
        return;
    }
    if(ui->colorComboBox->currentText() == "Yellow") {
        c = Yellow;
        setListsBackGround(c);
        updateListBackground(c);
        return;
    }

}

void MainToDoPanel::logOutPBClicked() {
    MainPanel *panel = new MainPanel(user);
    panel->show();
    this->close();
}
// // // //

void MainToDoPanel::updateListBackground(Color c) {
    Lists tmpList;

    for(auto it = listButtonMap.begin(); it != listButtonMap.end(); ++it) {
        if(it.key()->isChecked()) {
            tmpList = it.value();
            break;
        }
    }

    tmpList.setColor(c);

    for(auto it = listButtonMap.begin(); it != listButtonMap.end(); ++it) {
        if(it.key()->isChecked()) {
            it.value() = tmpList;
            break;
        }
    }

    Users tmpUser = user[loginUsername];
    tmpUser.setLists(tmpList.getListID(), tmpList);
    user[loginUsername] = tmpUser;
}

void MainToDoPanel::getPDFOutPut () {

}

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

    cleanStack();

    std::list<Lists> tmpList = userTmp.getLists();
    LinkList<Task> taskList;

    for(auto it = tmpList.begin(); it != tmpList.end(); ++it) {
        taskList = it->getTask();
        Node<Task> *tmp = taskList.getHeadNode();
        while (tmp) {
            addWidgetToScrollArea(qobject_cast<QVBoxLayout*>(ui->taskScrollAFrame->layout()), tmp->getData());
        }
    }
}
void MainToDoPanel::setUsersMyDayInfo () {
    unCheckedListButton();
    Users userTmp = user[loginUsername];
    QDate Today;
    int day = Today.currentDate().day();

    cleanStack();

    std::list<Lists> tmpList = userTmp.getLists();
    LinkList<Task> taskList;

    for(auto it = tmpList.begin(); it != tmpList.end(); ++it) {
        taskList = it->getTask();
        Node<Task> *tmp = taskList.getHeadNode();
        while (tmp) {
            if(tmp->getData().getReminder().day() == day) {
                addWidgetToScrollArea(qobject_cast<QVBoxLayout*>(ui->myDayScrollAFrame->layout()), tmp->getData());
                tmp = tmp->getNextNode();
            }

        }
    }

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
    QString buttonTitle = ui->taskNameLE->text();

    QPushButton *taskLabel = new QPushButton(buttonTitle);

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
        completePB->setIcon(circleFill);
    }
    else {
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
    layoutMap.insert(widget, itemLayout);
    detailsMap.insert(taskLabel, task.getDetails());

    connect(completePB, SIGNAL(clicked()), this, SLOT(taskCompletePBClicked()));
    connect(taskLabel, SIGNAL(clicked()), this, SLOT(showTaskDetails()));
}
void MainToDoPanel::addNewTaskInfo (Task& task) {
    task.setTitle(ui->taskNameLE->text());
    task.setDetails(ui->detailsTE->toPlainText());
    task.setAssignedUser(ui->assignToOtherLE->text());
    task.setFavorite(ui->favPB->isChecked());
    task.setCompleted(ui->completePBSideMenu->isChecked());
    task.setReminder(ui->calendarWidget->selectedDate());
}
void MainToDoPanel::addNewTaskToUserLists(Task & task) {
    Lists selectedList;
    for(auto it = listButtonMap.begin(); it != listButtonMap.end(); it++)
        if(it.key()->isChecked()) {
            selectedList = it.value();
            break;
        }

    selectedList.addTask(task);

    for(auto it = listButtonMap.begin(); it != listButtonMap.end(); ++it)
        if(it.key()->isChecked()) {
            it.value() = selectedList;
            break;
        }

    Users userTmp = user[loginUsername];
    userTmp.setLists(selectedList.getListID(), selectedList);

    user[loginUsername] = userTmp;
}

void MainToDoPanel::addListsTaskItems(Task task) {
    QVBoxLayout *frameLayout = qobject_cast<QVBoxLayout*>(ui->listsScrollAFrame->layout());

    QHBoxLayout *itemLayout = new QHBoxLayout;
    QString buttonTitle = task.getTitle();

    QWidget *widget = new QWidget;

    widget->setStyleSheet(
        "QWidget {"
        "background-color: rgb(50, 50, 50);"
        "border-radius : 5px;"
        "}"
        );

    QPushButton *taskLabel = new QPushButton(buttonTitle);

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
    } else {
        completePB->setChecked(false);
        completePB->setIcon(circleOutLine);
    }

    itemLayout->insertWidget(0, star);
    itemLayout->insertWidget(1, taskLabel);
    itemLayout->insertWidget(2, completePB);

    itemLayout->setContentsMargins(10, 1, 20, 0);
    itemLayout->setSpacing(0);

    widget->setLayout(itemLayout);

    frameLayout->insertWidget(0, widget);

    taskButtonMap.insert(completePB, task);
    layoutMap.insert(widget, itemLayout);
    detailsMap.insert(taskLabel, task.getDetails());

    connect(completePB, SIGNAL(clicked()), this, SLOT(taskCompletePBClicked()));
    connect(taskLabel, SIGNAL(clicked()), this, SLOT(showTaskDetails()));
}

void MainToDoPanel::addWidgetToScrollArea (QVBoxLayout* frame, Task task) {
    QHBoxLayout *itemLayout = new QHBoxLayout;
    QString buttonTitle = task.getTitle();

    QWidget *widget = new QWidget;
    widget->setStyleSheet(
        "QWidget {"
        "background-color: rgb(50, 50, 50);"
        "border-radius : 5px;"
        "}"
        );

    QPushButton *taskLabel = new QPushButton(buttonTitle);


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
    } else {
        completePB->setChecked(false);
        completePB->setIcon(circleOutLine);
    }

    itemLayout->insertWidget(0, star);
    itemLayout->insertWidget(1, taskLabel);
    itemLayout->insertWidget(2, completePB);

    itemLayout->setContentsMargins(10, 1, 20, 0);
    itemLayout->setSpacing(0);

    widget->setLayout(itemLayout);

    frame->insertWidget(0, widget);

    taskButtonMap.insert(completePB, task);
    layoutMap.insert(widget, itemLayout);
    detailsMap.insert(taskLabel, task.getDetails());

    connect(completePB, SIGNAL(clicked()), this, SLOT(taskCompletePBClicked()));
    connect(taskLabel, SIGNAL(clicked()), this, SLOT(showTaskDetails()));

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

void MainToDoPanel::cleanStack () {

    for(auto it = layoutMap.begin(); it != layoutMap.end(); it++) {

        while(it.value()->count() != 0) {
            QLayoutItem* item = it.value()->takeAt(0);
            delete item->widget();
            delete item;
        }
        delete it.value();
        delete it.key();
    }

    layoutMap.clear();
}

void MainToDoPanel::cleanSideTaskMenu () {
    ui->taskNameLE->clear();
    ui->detailsTE->clear();
    ui->assignToOtherLE->clear();
}


