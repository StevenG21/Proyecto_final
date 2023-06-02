#include "lapiz.h"
#include <iostream>
#include <QtCore>
using namespace std;

lapiz::lapiz(QObject *parent) : QObject(parent)
{
    gravedad = 3;
    reboteSuelo = false;
    alturainicial = 450;
    vel = 45;
    a = 70;
    vely = vel * sin(a*M_PI/180.0);
    velx = vel * cos(a*M_PI/180.0);
    timer = new QTimer;
        connect(timer, SIGNAL(timeout()), this, SLOT(actualizar())); //Se encarga de actualizar la posicion y el dibujado
        timer->start(4);

    imagen.load(":/Sprites/lapiz.png");

cout <<vely<<" : "<<velx<<endl;
}

QRectF lapiz::boundingRect() const
{
   return QRectF(pos.x(),500-imagen.height()-pos.y(), imagen.width(), imagen.height());

}

void lapiz::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{QPointF center(imagen.width() / 2.0, imagen.height() / 2.0);

    painter->save();

    // Rotar el lápiz en el ángulo deseado
    painter->translate(pos.x(), 500 - imagen.height() - pos.y());
    painter->rotate(-angulo);
    painter->translate(-pos.x(), -(500 - imagen.height() - pos.y()));

    painter->drawPixmap(pos.x(), 500 - imagen.height() - pos.y(), imagen, 0, 0, imagen.width(), imagen.height());

    painter->restore();

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void lapiz::setgravity()
{
  //  efectos = new QTimer;

    gravedad = gravedad + 2;
            this->update();

   // if(efectos->remainingTime()<=0){
    //    delete efectos;
   //     gravedad = 3;
      // emit tiempo_efecto();




}

void lapiz::actualizar()  //Funcion donde se genera el movimiento
{

  pos.setX(posini.x()+velx*t);
  pos.setY(posini.y()+(vely*t)-0.5*gravedad*pow(t,2));  //Tiro parabolico



  if(pos.y()<0){    //Rebotes
     t=0;
     vely = vely*0.6; //Coeficiente de rebote
     velx = velx*0.7; //Coeficiente de friccion
     posini.setY(pos.y());
     posini.setX(pos.x());

  }



if((velx<=0.1) && (vely<=0.1)){  //Detiene el timer y emita una señal para eliminar el proyectil
    timer->stop();
    delete timer;
    emit deltepencil();
}

t+= 0.060;
angulo= (atan(pos.y()/pos.x()))*180/M_PI;

//cout << angulo <<endl;

}


