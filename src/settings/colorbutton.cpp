#include "colorbutton.h"

ColorButton::ColorButton(QWidget *parent)
    : QPushButton(parent)
{
    connect(this, &QPushButton::clicked, this, &ColorButton::onClicked);
}

void ColorButton::setColor(QColor color)
{
    m_color = color;

    QRect rect(5, 5, size().width() - 10, size().height() - 10);
    repaint(rect);
}

void ColorButton::onClicked()
{
    QColorDialog dialog(m_color, this);

    if (dialog.exec() == QDialog::Accepted) {
        m_color = dialog.selectedColor();

        emit colorChanged(m_color);
    };
}

void ColorButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(m_color);

    QRect rect(5, 5, size().width() - 10, size().height() - 10);

    painter.drawRect(rect);
}
