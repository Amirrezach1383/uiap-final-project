#ifndef LOGINPANEL_H
#define LOGINPANEL_H

#include <QMainWindow>
#include <users.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginPanel;
}
QT_END_NAMESPACE

class LoginPanel : public QMainWindow
{
    Q_OBJECT

public:
    LoginPanel(std::map<QString, Users>, QWidget *parent = nullptr);
    ~LoginPanel();

    std::map<QString, Users> user;
private:
    Ui::LoginPanel *ui;
};

#endif // LOGINPANEL_H
