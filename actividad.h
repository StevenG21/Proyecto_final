#ifndef ACTIVIDAD_H
#define ACTIVIDAD_H
#include <QTimer>
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QDebug>

class actividad : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
QPixmap imagen;
QTimer *timer;
float t,tacel;
float fila,columna;
int random;

public:
    actividad(QObject *parent = nullptr);
QRectF boundingRect() const;
void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
QPointF pos;
void setnewpos(QPointF np){
    pos = np;


}
signals:
void deletebook();
public slots:
void nextsprite();
void movimiento();
};

#endif // ACTIVIDAD_H
