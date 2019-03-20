#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QSize>
#include <QPoint>
#include <QByteArray>
#include <QFont>

class Settings
{
public:
    typedef struct {
        QSize size;
        QPoint pos;
        QByteArray splitter;
        bool multipleInstances;
        bool showTrayIcon;
        bool minimizeToTrayIcon;
    } MainWindowSettings;

    typedef struct {
        QFont font;
        int fontSize;
    } EditorSettings;

    Settings();

    MainWindowSettings getWindowSettings();
    void setWindowSettings(MainWindowSettings &mwSettings);

    EditorSettings getEditorSettings();
    void setEditorSettings(EditorSettings &eSettings);

private:
    QSettings settings;
};

#endif // SETTINGS_H
