#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QVector>
#include "newton.h"
#include "apple.h"
#include "lapiz.h"
#include <QPixmap>
#include <QMovie>
#include <QMouseEvent>
#include <QTime>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    int v_limit;
    int h_limit;

    void keyPressEvent(QKeyEvent *event) ;
    void mouseMoveEvent(QMouseEvent *event) ;
    void mousePressEvent(QMouseEvent *event);




    MainWindow(QWidget *parent = nullptr);

    void disparar();


    ~MainWindow();

private:
    QPixmap fondo;
    QVector <float> puntos;
    QVector<apple*> apples;
    QVector<lapiz*> pencil;
    QTimer *timer;
    QTimer *spawnapples;
    QTimer *Tiemponivel;
    Newton *n;
    QPixmap mapascaled;
    QPixmap niveles(int);
    QMovie *movie;
    QTime time;
    int nivel = 1;
    bool efecto;
    float angulo;

    QGraphicsScene *scene;
    Ui::MainWindow *ui;
public slots:
       void game();
       void generarmanzana();
       void deleteapple();
       void deletepencil();
       void refresh();
       void puntaje();
       void cronometro();
    //   void nivel1();
      // void nivel2();
      // void nivel3();
      // void nivel4();
      // void nivel5();



};
#endif // MAINWINDOW_H
