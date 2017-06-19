#ifndef FILES_H
#define FILES_H
#include <QGraphicsItem>
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <QMainWindow>
#include <QtWidgets>
#include "fileentry.h"

class Files : public QGraphicsItem
{
public:
    Files(char * nombre, bool esFold, int posX, int posY, bool selected);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void updateFile(bool);

    QImage * image;
    QRectF rect;
    char * nombre;
    int posX, posY;
    bool esFold, selected;
};

#endif // FILES_H
