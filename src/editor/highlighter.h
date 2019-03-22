#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>
#include <QRegularExpression>

#include "settings.h"

class Highlighter : public QSyntaxHighlighter
{
public:
    Highlighter(QTextDocument *parent = nullptr);

    void loadSettings(Settings::EditorSettings eSettings);

protected:
    void highlightBlock(const QString &text) override;

private:
    QVector<Settings::HighlightingRule> highlightingRules;
};

#endif // HIGHLIGHTER_H
