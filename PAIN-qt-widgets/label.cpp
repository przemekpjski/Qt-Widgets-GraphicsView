#include "label.h"

#include <QGraphicsSimpleTextItem>
#include <QtWidgets>

Label::Label(const QString &text)
    : textItem(new QGraphicsSimpleTextItem(text, this)) // tr(text) ?
{
    textItem->setBrush(Qt::green);
    textItem->setPen(QPen(Qt::red));
    textItem->setFont({"Helvetica [Cronyx]", 8});

    setBrush(Qt::yellow);
    setRect(textItem->boundingRect());

    //setFlags(ItemIsMovable | ItemIsSelectable);
}

void Label::setText(const QString &text)
{
    textItem->setText(text);
    setRect(textItem->boundingRect());
}

QString Label::text() const
{
    return textItem->text();
}
