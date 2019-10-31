#include <QApplication>
#include <QMessageBox>

#include "mainmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("jurask");
    QCoreApplication::setApplicationName("powershed");
    MainMenu menu;
    menu.show();
    return a.exec();
}
