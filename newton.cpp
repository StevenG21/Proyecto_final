#include "newton.h"
#define alto 150
#define ancho 150
Newton::Newton(QObject *parent) : QObject(parent)

{
 pos = QPointF(0,0);
    movie = new QMovie(":/Sprites/Newtonbase.gif");
     movie->start();
     pixmap = movie->currentPixmap().scaled(alto, ancho);

     timer = new QTimer;
         connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(10);
}

QRectF Newton::boundingRect() const
{

    return QRectF(pos.x(),pos.y(),pixmap.width(),pixmap.height());
}

void Newton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  //  painter->setBrush(Qt::darkBlue);        //asigna el color
    painter->drawPixmap(pos.x(),pos.y(),pixmap);   //dibuja una elipse encerrada en la boundingRect
    Q_UNUSED(option);
    Q_UNUSED(widget);

}

void Newton::update()
{
   pixmap = movie->currentPixmap().scaled(alto,ancho);
    QGraphicsItem::update();
}
