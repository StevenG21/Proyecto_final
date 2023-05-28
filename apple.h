#ifndef APPLE_H
#define APPLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class apple : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
    QPixmap imagen;
       float vel;
public:
    explicit apple(QObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPointF pos;

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
    void actualizar();
signals:
void colision();
};

#endif // APPLE_H
