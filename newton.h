#ifndef NEWTON_H
#define NEWTON_H
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QMovie>
#include <QTimer>
#include <QLabel>
#include <iostream>

using namespace std;
enum animaciones {base,manzana,prisma


    };

class Newton : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:

     explicit Newton(QObject *parent = nullptr);
    bool end=false;
    int frame;
    QRectF boundingRect() const;    //necesario definirla, devuelve el rectangulo que encierra el objeto
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //define como se pintara el objeto
    QPointF pos;
    QPointF vel;
    QMovie *movie;
    QPixmap pixmap;
    QTimer* timer;
    animaciones a;
    float getposx(){
        return pos.x();
    }
    float getposy(){
        return pos.y();
    }
    void setpos(QPointF newpos){
        pos = newpos;
    }

    void animaciones(int);

public slots:
    void update();

signals:
    void endframe();

};

#endif // NEWTON_H
