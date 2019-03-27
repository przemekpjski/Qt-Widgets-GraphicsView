#ifndef LABEL_H
#define LABEL_H

#include <QGraphicsRectItem>

// : public virtual QGraphicsRectItem, QGraphicsSimpleTextItem
class Label : public QGraphicsRectItem
{
public:
    Label(const QString &text = "");

    void setText(const QString &text);
    QString text() const;

private:
    QGraphicsSimpleTextItem *textItem;
};

#endif // LABEL_H
