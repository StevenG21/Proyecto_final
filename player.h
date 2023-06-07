#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

#include <iostream>

class player : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    float fila,columna,ancho;
    explicit player(QObject *parent = nullptr);
    QRectF boundingRect() const;    //necesario definirla, devuelve el rectangulo que encierra el objeto
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //define como se pintara el objeto
    QPointF pos;
    QPixmap pixmap;
    float getposx(){
        return pos.x();
    }
    float getposy(){
        return pos.y();
    }
    void setpos(QPointF newpos){
        pos = newpos;
    }
signals:

public slots:
    void sprite(int);

};

#endif // PLAYER_H
