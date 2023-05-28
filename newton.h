#ifndef NEWTON_H
#define NEWTON_H
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QMovie>
#include <QTimer>

class Newton : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
     explicit Newton(QObject *parent = nullptr);

    QRectF boundingRect() const;    //necesario definirla, devuelve el rectangulo que encierra el objeto
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //define como se pintara el objeto
    QPointF pos;
    QPointF vel;
    QMovie *movie;
    QPixmap pixmap;
    QTimer* timer;
    float getposx(){
        return pos.x();
    }
    float getposy(){
        return pos.y();
    }
    void setpos(QPointF newpos){
        pos = newpos;
    }

public slots:
    void update();



};

#endif // NEWTON_H
