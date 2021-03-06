#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QMessageBox>
#include <QCommandLineParser>

#include <iostream>
#include <unistd.h>
#include <sys/types.h>

#include "consts.h"
#include "runguard.h"
#include "settings.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationName(APP_DEVELOPER);
    QCoreApplication::setOrganizationDomain(APP_DOMAIN);

    QCommandLineParser parser;
    parser.setApplicationDescription("Simple GUI editor for /etc/hosts file");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption noCheckUserOption("u", "Disable check if user is root");
    parser.addOption(noCheckUserOption);

    parser.process(a);

    bool noCheckUser = parser.isSet(noCheckUserOption);

    auto userId = getuid();

    if (!noCheckUser && userId != 0) {
        QMessageBox confirm;
        confirm.setWindowTitle("Run as root");
        confirm.setTextFormat(Qt::TextFormat::RichText);
        confirm.setText("This application should be run as a root user<br>because it edits <b>/etc/hosts</b> file."
                        "<br><br>"
                        "<b>Restart as root entering sudo password?</b>");
        confirm.setIcon(QMessageBox::Warning);
        confirm.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        confirm.setDefaultButton(QMessageBox::Yes);

        if (confirm.exec() == QMessageBox::Yes) {

            system(QString("gksudo %1").arg(argv[0]).toStdString().c_str());

        } else {
            confirm.close();
        };

        exit(0);
    }

    QString mSharedKey = "qEtcHosts_application123123";
    RunGuard guard(mSharedKey);

    Settings settings;

    if (!settings.getWindowSettings().multipleInstances && !guard.tryToRun()) {
        std::cout << "Another instance of application has already running." << std::endl;
        std::cout << "Application shared memory key: " << mSharedKey.toStdString() << std::endl << "Exit..." << std::endl;

        return 0;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
