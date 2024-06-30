#ifndef SIGNUPPANEL_H
#define SIGNUPPANEL_H

#include <QMainWindow>

namespace Ui {
class SignUpPanel;
}

class SignUpPanel : public QMainWindow
{
    Q_OBJECT

public:
    SignUpPanel(QWidget *parent = nullptr);
    ~SignUpPanel();

private:
    Ui::SignUpPanel *ui;
};

#endif // SIGNUPPANEL_H
