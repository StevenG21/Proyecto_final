#include "lapiz.h"
#include <iostream>
#include <QtCore>
using namespace std;
#define gravedad 3
lapiz::lapiz(QObject *parent) : QObject(parent)
{
    reboteSuelo = false;
    alturainicial = 450;
    vel = 25;
    a = 60;
    vely = vel * sin(a*M_PI/180.0);
    velx = vel * cos(a*M_PI/180.0);
    timer = new QTimer;
        connect(timer, SIGNAL(timeout()), this, SLOT(actualizar()));
        timer->start(5);

    imagen.load(":/Sprites/apple.png");

cout <<vely<<" : "<<velx<<endl;
}

QRectF lapiz::boundingRect() const
{
   return QRectF(pos.x(),500-imagen.height()-pos.y(), imagen.width(), imagen.height());
}

void lapiz::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
painter->drawPixmap(pos.x(),500-imagen.height()-pos.y(),imagen,0,0,imagen.width(),imagen.height());
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void lapiz::actualizar()
{

  pos.setX(posini.x()+velx*t);
  pos.setY(posini.y()+(vely*t)-0.5*gravedad*pow(t,2));

  if(pos.y()<0){
     t=0;
     vely = vely*0.9;
     velx = velx*0.8;
     posini.setY(pos.y());
     posini.setX(pos.x());

  }



if((velx<=0.1) && (vely<=0.1)){
    timer->stop();
    delete timer;
}

t+= 0.060;
cout << velx <<" "<<vely<< " Time: "<<t<<endl;

}


