#ifndef LAPIZ_H
#define LAPIZ_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <cmath>
#include <QTimer>

class lapiz : public QObject, public QGraphicsItem
{
    Q_OBJECT

private:
    bool reboteSuelo;
    float alturainicial;
    float t=0;
      QPointF pos;
      QPointF posini;
    float a; //Angulo
    QPixmap imagen;
       float vel;
       float velx;
       float vely;
    QTimer* timer;

public:
    explicit lapiz(QObject *parent = nullptr);

       QRectF boundingRect() const;
       void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


       float getposx(){
           return pos.x();
       }
       float getposy(){
           return pos.y();
       }
       void setpos(QPointF newpos){
           posini = newpos;
           posini.setY(500-newpos.y());
       }
       void setangle(float na){
           a = na;
       }
public slots:
       void actualizar();

signals:

};

#endif // LAPIZ_H
