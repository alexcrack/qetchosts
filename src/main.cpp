#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>

#include "consts.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationName(APP_DEVELOPER);
    QCoreApplication::setOrganizationDomain(APP_DOMAIN);

    MainWindow w;
    w.show();

    return a.exec();
}
