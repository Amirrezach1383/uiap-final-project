#ifndef LOGINPANEL_H
#define LOGINPANEL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginPanel;
}
QT_END_NAMESPACE

class LoginPanel : public QMainWindow
{
    Q_OBJECT

public:
    LoginPanel(QWidget *parent = nullptr);
    ~LoginPanel();

private:
    Ui::LoginPanel *ui;
};

#endif // LOGINPANEL_H
