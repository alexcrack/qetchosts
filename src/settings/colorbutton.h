#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QColorDialog>
#include <QColor>

#include <QDebug>

class ColorButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor color MEMBER m_color NOTIFY colorChanged)

public:
    ColorButton(QWidget *parent = nullptr);

    void setColor(QColor color);

signals:
    void colorChanged(QColor color);

private:
    QColor m_color;

private slots:
    void onClicked();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // COLORBUTTON_H
