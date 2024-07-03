#include "mainpanel.h"
#include <signuppanel.h>
#include <QApplication>
#include <loginpanel.h>
#include <maintodopanel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainToDoPanel w;
    // MainPanel q;
    // q.show();
    w.show();

    return a.exec();
}
