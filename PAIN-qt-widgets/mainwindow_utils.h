#ifndef MAINWINDOW_UTILS_H
#define MAINWINDOW_UTILS_H

#include <QWidget>
#include <QButtonGroup>
#include <QToolButton>
#include <QGridLayout>
#include <QLabel>

namespace mainwindow_utils {

inline QWidget* createToolButton(const QIcon &buttonIcon, const QString &labelString, QButtonGroup &buttonGroup, int buttonId, const QSize &iconSize = QSize(50, 50))
{
    QToolButton* button = new QToolButton;
    button->setIcon(buttonIcon);
    button->setIconSize(iconSize);
    button->setCheckable(true);
    buttonGroup.addButton(button, buttonId);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(labelString), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

}

#endif // MAINWINDOW_UTILS_H
