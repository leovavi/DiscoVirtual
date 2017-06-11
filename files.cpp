#include "files.h"

Files::Files(FileEntry * fe, int posX, int posY, bool selected){
    this->fe = fe;
    QString path = "C:\\Users\\Leovavi\\Documents\\UNITEC\\Recursos\\File Explorer\\";
    path += (fe->esFold() ? "folder.png" : "texto.png");

    image = new QImage(path);
    this->posX = posX;
    this->posY = posY;
    this->selected = selected;
}

QRectF Files::boundingRect() const{
    return QRectF(posX, posY, 100, 130);
}

void Files::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    rect = boundingRect();

    if(selected){
        QColor color(135, 206, 250);
        painter->fillRect(rect, color);
    }
    else{
        QColor color(255, 255, 255);
        painter->fillRect(rect, color);
    }

    painter->drawImage(rect, *image, QRectF(0,0,100,130));
    painter->drawText(QRectF(posX, posY+40, 100, 130), Qt::AlignCenter | Qt::TextWordWrap | Qt::TextDontClip, fe->getNombre());
}
