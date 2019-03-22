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

    settings.beginGroup("highlight");

    HighlightingRule rule;

    QTextCharFormat ipv4;
    ipv4.setForeground(QColor(8, 128, 64));
    ipv4.setFontWeight(QFont::Bold);
    rule.name = "IPv4 address";
    rule.pattern = QRegularExpression("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    rule.format = ipv4;
    eSettings.highlights.append(rule);

    QTextCharFormat ipv6;
    ipv6.setForeground(QColor(64, 128, 8));
    ipv6.setFontWeight(QFont::Bold);
    rule.name = "IPv6 address";
    rule.pattern = QRegularExpression("^(?:(?:(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):){6})(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):(?:(?:[0-9a-fA-F]{1,4})))|(?:(?:(?:(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9]))\\.){3}(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9])))))))|(?:(?:::(?:(?:(?:[0-9a-fA-F]{1,4})):){5})(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):(?:(?:[0-9a-fA-F]{1,4})))|(?:(?:(?:(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9]))\\.){3}(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9])))))))|(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})))?::(?:(?:(?:[0-9a-fA-F]{1,4})):){4})(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):(?:(?:[0-9a-fA-F]{1,4})))|(?:(?:(?:(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9]))\\.){3}(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9])))))))|(?:(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):){0,1}(?:(?:[0-9a-fA-F]{1,4})))?::(?:(?:(?:[0-9a-fA-F]{1,4})):){3})(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):(?:(?:[0-9a-fA-F]{1,4})))|(?:(?:(?:(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9]))\\.){3}(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9])))))))|(?:(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):){0,2}(?:(?:[0-9a-fA-F]{1,4})))?::(?:(?:(?:[0-9a-fA-F]{1,4})):){2})(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):(?:(?:[0-9a-fA-F]{1,4})))|(?:(?:(?:(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9]))\\.){3}(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9])))))))|(?:(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):){0,3}(?:(?:[0-9a-fA-F]{1,4})))?::(?:(?:[0-9a-fA-F]{1,4})):)(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):(?:(?:[0-9a-fA-F]{1,4})))|(?:(?:(?:(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9]))\\.){3}(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9])))))))|(?:(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):){0,4}(?:(?:[0-9a-fA-F]{1,4})))?::)(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):(?:(?:[0-9a-fA-F]{1,4})))|(?:(?:(?:(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9]))\\.){3}(?:(?:25[0-5]|(?:[1-9]|1[0-9]|2[0-4])?[0-9])))))))|(?:(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):){0,5}(?:(?:[0-9a-fA-F]{1,4})))?::)(?:(?:[0-9a-fA-F]{1,4})))|(?:(?:(?:(?:(?:(?:[0-9a-fA-F]{1,4})):){0,6}(?:(?:[0-9a-fA-F]{1,4})))?::))))\\b");
    rule.format = ipv4;
    eSettings.highlights.append(rule);

    QTextCharFormat host;
    host.setForeground(QColor(128, 64, 8));
    rule.name = "Host name";
    rule.pattern = QRegularExpression("[\\s\\t].+$");
    rule.format = host;
    eSettings.highlights.append(rule);

    QTextCharFormat comment;
    comment.setForeground(QColor(16, 128, 192));
    comment.setFontItalic(true);
    rule.name = "Comment";
    rule.pattern = QRegularExpression("#[^\n]*");
    rule.format = comment;
    eSettings.highlights.append(rule);

    for (auto &r : eSettings.highlights) {
        settings.beginGroup(r.name);

        r.format.setForeground(QColor(settings.value("foreground", QColor(r.format.foreground().color())).toString()));
        r.format.setBackground(QColor(settings.value("background", QColor(0, 0, 0, 0)).toString()));
        r.format.setFontWeight(settings.value("bold", r.format.fontWeight()).toInt());
        r.format.setFontItalic(settings.value("italic", r.format.fontItalic()).toBool());

        settings.endGroup();
    }

    settings.endGroup(); // highlight

    settings.endGroup(); // Editor

    return eSettings;
}

void Settings::setEditorSettings(Settings::EditorSettings &eSettings)
{
    settings.beginGroup("Editor");

    settings.setValue("font", eSettings.font.toString());

    settings.beginGroup("highlight");

    for (auto &r : eSettings.highlights) {
        settings.beginGroup(r.name);

        settings.setValue("foreground", QColor(r.format.foreground().color()));
        settings.setValue("background", QColor(r.format.background().color()));
        settings.setValue("bold", r.format.fontWeight());
        settings.setValue("italic", r.format.fontItalic());

        settings.endGroup();
    }

    settings.endGroup(); // highlight

    settings.endGroup(); // Editor
}
