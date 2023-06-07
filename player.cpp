#include "player.h"

#define alto 115
player::player(QObject *parent) : QObject(parent)
{
    ancho = 76.75;
    fila = columna=0;
    pixmap.load(":/Sprites/player.png");
pos = QPointF(100,450);
}

QRectF player::boundingRect() const
{
return QRectF((-ancho/2) + pos.x(),-alto/2,ancho,alto);
}

void player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap((-ancho/2+pos.x()),-alto/2,pixmap,columna,fila,ancho,alto);
   // painter->drawRect(boundingRect());

    Q_UNUSED(option);
    Q_UNUSED(widget);


}

void player::sprite(int dir)
{
    switch (dir) {
    case 1:  // Derecha
        fila = 2*alto;
        columna += ancho;
        if(columna >= pixmap.width()){
            columna = 0;
        }

        break;
    case 2: // Izquierda
        fila = alto;
        columna += ancho;
        if(columna >= pixmap.width()){
            columna = 0;
        }

    }
    this->update(-ancho/2,-alto/2,ancho,alto);
    update();
}
