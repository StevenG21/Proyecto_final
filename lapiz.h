#ifndef LAPIZ_H
#define LAPIZ_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <cmath>
#include <QTimer>
#include <QSoundEffect>

class lapiz : public QObject, public QGraphicsItem
{
    Q_OBJECT

private:
    QSoundEffect *sonido;
    float gravedad;
    float angulo;
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
    QTimer *efectos;

public:
    explicit lapiz(QObject *parent = nullptr);

       QRectF boundingRect() const;
       void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
       void setgravity(int);


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
       float getangle(){
           return angulo;
       }
public slots:
       void dir_pencil();
       void actualizar();
private slots:
signals:
       void tiempo_efecto();
       void deltepencil();

};

#endif // LAPIZ_H
