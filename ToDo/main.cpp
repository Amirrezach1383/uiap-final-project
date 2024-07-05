#include "mainpanel.h"
#include <QApplication>

bool readDataFromDB ();


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainPanel w(*new std::map <QString, Users>);
    w.show();

    return a.exec();
}

bool readDataFromDB () {

    return true;


}
