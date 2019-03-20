#include "settings.h"

Settings::Settings()
{

}

Settings::MainWindowSettings Settings::getWindowSettings()
{
   MainWindowSettings mwSettings;

   settings.beginGroup("MainWindow");

   mwSettings.pos = settings.value("pos", QPoint(10, 10)).toPoint();
   mwSettings.size = settings.value("size", QSize(1000, 500)).toSize();
   mwSettings.splitter = settings.value("splitter").toByteArray();
   mwSettings.multipleInstances = settings.value("multiple", false).toBool();
   mwSettings.showTrayIcon = settings.value("trayIcon", true).toBool();
   mwSettings.minimizeToTrayIcon = settings.value("minimizeToTray", true).toBool();

   settings.endGroup();

   return mwSettings;
}

void Settings::setWindowSettings(Settings::MainWindowSettings &mwSettings)
{
    settings.beginGroup("MainWindow");

    settings.setValue("pos", mwSettings.pos);
    settings.setValue("size", mwSettings.size);
    settings.setValue("splitter", mwSettings.splitter);
    settings.setValue("multiple", mwSettings.multipleInstances);
    settings.setValue("trayIcon", mwSettings.showTrayIcon);
    settings.setValue("minimizeToTray", mwSettings.minimizeToTrayIcon);

    settings.endGroup();
}

Settings::EditorSettings Settings::getEditorSettings()
{
    EditorSettings eSettings;

    settings.beginGroup("Editor");

    QFont font;
    font.fromString(settings.value("font", "Courier,10,-1,5,50,0,0,0,1,0").toString());

    eSettings.font = font;;
    eSettings.fontSize = font.pointSize();

    settings.endGroup();

    return eSettings;
}

void Settings::setEditorSettings(Settings::EditorSettings &eSettings)
{
    settings.beginGroup("Editor");

    settings.setValue("font", eSettings.font.toString());
    settings.setValue("fontSize", eSettings.fontSize);

    settings.endGroup();
}
