#include "actividad.h"
#include <cmath>
#include <QRandomGenerator>
#define ancho 30
#define alto 30
actividad::actividad(QObject *parent) : QObject(parent)
{   tacel=0.0008;
    t=0;
    fila = columna = 0;
    imagen.load(":/Sprites/libros.png");
    timer = new QTimer;
    random = QRandomGenerator::global()->bounded(500);
    QTimer *t2 = nullptr;
    t2 = new QTimer;
    connect(t2, SIGNAL(timeout()), this, SLOT(nextsprite()));
        //connect(timer, SIGNAL(timeout()), this, SLOT(movimiento())); //Se encarga de actualizar la posicion y el dibujado
      //  timer->start(2);
        t2->start(1000);
}

QRectF actividad::boundingRect() const
{
    return QRectF(-ancho/2+pos.x()+random,-alto/2+pos.y(),ancho,alto);
}

void actividad::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(-ancho/2+pos.x()+random,-alto/2+pos.y(),imagen,columna,fila,ancho,alto);
  // painter->setPen(Qt::red);
  //  painter->drawRect(boundingRect());
}

void actividad::nextsprite()
{

    columna += ancho;
    if(columna >=imagen.width()){
        columna = 0;
        fila += alto;
            if(fila >= imagen.height()){
                fila=0;
            }
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}

void actividad::movimiento()
{

    pos.setX(200*(cos(8*t)-pow(cos(t),3)));
    pos.setY(200*(sin(8*t)-pow(sin(t),3)));

    t +=tacel;
    tacel += 0.0000001;

}
