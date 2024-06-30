#include "mainpanel.h"
#include <signuppanel.h>
#include <QApplication>
#include <loginpanel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginPanel w;
    MainPanel q;
    q.show();
    w.show();

    return a.exec();
}
