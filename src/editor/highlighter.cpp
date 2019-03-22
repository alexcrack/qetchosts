#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter (parent)
{

}

void Highlighter::loadSettings(Settings::EditorSettings eSettings)
{
    highlightingRules = eSettings.highlights;

    rehighlight();
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const Settings::HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);

        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);
}
