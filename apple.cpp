#include "apple.h"
#include <iostream>
#include <cmath>

using namespace std;

apple::apple(QObject *parent) : QObject(parent)
{
vel = 1;
imagen.load(":/Sprites/apple.png");

}

QRectF apple::boundingRect() const
{
    return QRectF(pos.x(), pos.y(), imagen.width(),imagen.height());
}

void apple::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->drawPixmap(pos.x(),pos.y(),imagen,0,0,imagen.width(),imagen.height());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void apple::actualizar() //Mueve las manzanas que caen
{
    pos.setY(getposy() + vel);
    if(getposy()<=0){
        vel = vel*(-1.1);
    }

    if(getposy()>=500-imagen.height()){  //Cuando llegan al borde se eliminan

        emit colision();  //Emite una señal si colisiona con el borde inferior

}

}

