#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QSize>
#include <QPoint>
#include <QByteArray>
#include <QFont>
#include <QTextCharFormat>
#include <QRegularExpression>

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

    typedef struct
    {
        QString name;
        QRegularExpression pattern;
        QTextCharFormat format;
    } HighlightingRule;

    typedef struct {
        QFont font;
        QVector<HighlightingRule> highlights;
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
