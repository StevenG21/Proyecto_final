#include "newton.h"
#define alto 150
#define ancho 150


Newton::Newton(QObject *parent) : QObject(parent)

{

 movie = new QMovie(":/Sprites/base.gif");
 frame = movie->frameCount();
 cout << "frames: "<<frame<<endl;
    pos = QPointF(0,500-150);
    movie->start();
    pixmap = movie->currentPixmap().scaled(alto, ancho);
    a=base;

     timer = new QTimer;
         connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(1);
}

QRectF Newton::boundingRect() const
{

    return QRectF(pos.x(),pos.y(),pixmap.width(),pixmap.height());
}

void Newton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        painter->transform();
        painter->drawPixmap(pos, pixmap);
        Q_UNUSED(option);
        Q_UNUSED(widget);

}

void Newton::animaciones(int x)
{
    switch (x) {
    case 1:
        movie->stop();
        delete movie;
        end = false;
        a = base;
        movie = new QMovie(":/Sprites/base.gif");
        frame = movie->frameCount();
        movie->setSpeed(100);
         movie->start();
        pixmap = movie->currentPixmap().scaled(alto, ancho);
        break;

    case 2:
        movie->stop();
        delete movie;
        end = false;
        a = manzana;
        movie = new QMovie(":/Sprites/spawnapple.gif");
        frame = movie->frameCount();
        movie->setSpeed(120);
         movie->start();
        pixmap = movie->currentPixmap().scaled(alto, ancho);
        break;

    case 3:
        movie->stop();
        delete movie;
        end = false;
        a = tesla;
        movie = new QMovie(":/Sprites/elprofe.gif");
        frame = movie->frameCount();
        movie->setSpeed(120);
         movie->start();
        pixmap = movie->currentPixmap().scaled(alto, ancho);
        break;
    }


}


void Newton::update()
{
    switch (a) {
    case base:
        pixmap = movie->currentPixmap().scaled(alto,ancho);

        break;
    case manzana:
        if((movie->currentFrameNumber()>=frame - 1)&& !end){
            emit endframe();
            movie->stop();

            end = true;
            animaciones(1);
        }
        pixmap = movie->currentPixmap().scaled(alto,ancho);

        break;

    case tesla:
    pixmap = movie->currentPixmap().scaled(alto,ancho);
        break;

    }





}
