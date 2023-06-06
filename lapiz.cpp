#include "lapiz.h"
#include <iostream>
#include <QtCore>
#define ancho 34
#define alto 5
using namespace std;

lapiz::lapiz(QObject *parent) : QObject(parent)
{
    gravedad = 2.5;
    reboteSuelo = false;
    alturainicial = 450;
    vel = 40;
    a = 90;
    vely = vel * sin(a*M_PI/180.0);
    velx = vel * cos(a*M_PI/180.0);

    //timer = new QTimer;
    //    connect(timer, SIGNAL(timeout()), this, SLOT(actualizar())); //Se encarga de actualizar la posicion y el dibujado
   //     timer->start(4);
sonido = new QSoundEffect;
sonido->setSource((QUrl("qrc:/Sonidos/lapizsound.wav")));
sonido->setVolume(0.51);
    imagen.load(":/Sprites/lapiz.png");


cout <<vely<<" : "<<velx<<endl;
}

QRectF lapiz::boundingRect() const
{
   return QRectF( pos.x(),500-imagen.height()-pos.y(), imagen.width(), imagen.height());

}

void lapiz::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->save();

    // Rotar el lápiz en el ángulo deseado
    painter->translate(pos.x(), 500 - imagen.height() - pos.y());
    painter->rotate(-a);
    painter->translate(-pos.x(), -(500 - imagen.height() - pos.y()));

    painter->drawPixmap(pos.x(), 500 - imagen.height() - pos.y(), imagen, 0, 0, imagen.width(), imagen.height());



  //  painter->setPen(Qt::red);
 //    painter->drawRect(boundingRect());
     painter->restore();
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void lapiz::setgravity(int g)
{

    gravedad = g;
    this->update();

}

void lapiz::dir_pencil()

{

    vely = vel * sin(a*M_PI/180.0);
    velx = vel * cos(a*M_PI/180.0);

}

void lapiz::actualizar()  //Funcion donde se genera el movimiento
{
   // vely = vel * sin(a*M_PI/180.0);
 //   velx = vel * cos(a*M_PI/180.0);

  pos.setX(posini.x()+velx*0.8*t);
  pos.setY(posini.y()+(vely*t)-0.5*gravedad*pow(t,2));  //Tiro parabolico



  if(pos.y()<0.1+imagen.width()){    //Rebotes
     t=0;
     vely = vely*0.5; //Coeficiente de rebote
     velx = velx*0.6; //Coeficiente de friccion
     posini.setY(pos.y());
     posini.setX(pos.x());
    sonido->play();
     sonido->setVolume(sonido->volume()-0.1);
  }



if((velx<=0.1) && (vely<=0.1)){
   //Detiene el timer y emita una señal para eliminar el proyectil

    emit deltepencil();
}

if(pos.x()<=0.1){

    t=0;
    vely = vely*0.5; //Coeficiente de rebote
    velx = velx*0.6; //Coeficiente de friccion
    posini.setY(pos.y());
    posini.setX(pos.x());
    sonido->play();
    sonido->setVolume(sonido->volume()-0.1);

}
if(pos.x()>=800-imagen.width()){

    t=0;
    vely = vely*0.5; //Coeficiente de rebote
    velx = -velx*0.4; //Coeficiente de friccion
    posini.setY(pos.y());
    posini.setX(pos.x());
    sonido->play();
    sonido->setVolume(sonido->volume()-0.1);

}


t+= 0.090;

angulo =  (atan(pos.y()/pos.x()))*180/M_PI;

this->update();
}


