#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QString>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QVector>
#include "newton.h"
#include "apple.h"
#include "lapiz.h"
#include "player.h"
#include "actividad.h"
#include <QPixmap>
#include <QMovie>
#include <QTime>
#include <QDebug>
#include <QMultimedia>
#include <QMediaPlayer>
#include <QSoundEffect>
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
  //  void keyReleaseEvent(QKeyEvent *event);

    MainWindow(QWidget *parent = nullptr);

    void disparar(float,float,int);

    ~MainWindow();

private:
    QString nombrenivel;
    float ampl,frec,porcentaje;
    float  t;
    int potencia;
QMediaPlayer* nivel1theme;
QMediaPlayer* s1;
QSoundEffect *as;
int numlibros;
int bookcounter;
    QVector<apple*> applestoremove;
    QVector<actividad*> bookstoremove;
    player *jugador;
    QPixmap fondo;
    lapiz *pointerpen;
    float puntos;
    QVector<apple*> apples;
    QVector<lapiz*> pencil;
    QVector<actividad*> books;
    QTimer *timer;
    QTimer *Colitime;
    QTimer *timerbooks;
    QTimer *spawnapples;
    QTimer *Tiemponivel;
    QTimer *tdisparo;
    Newton *n;
    QPixmap mapascaled;
    QPixmap niveles(int);
    QMovie *movie;
    QTime time;
    int nivel = 1;
    bool efecto,tru;
    float angulo;
    float gravity;
    void newscene(int x);
    void setporcentaje(float);
    QGraphicsPixmapItem *gif;
    QGraphicsScene *scene;
    QGraphicsScene *nivel2;
    QGraphicsScene *Resultados;
    Ui::MainWindow *ui;
public slots:
       void power();
       void game();
       void generarmanzana();
       void generarlibro();
       void deleteapple();
       void deletebook();
       void deletepencil();
       void refresh();
       void spawn();
       void cronometro();
    //   void nivel1();
      // void nivel2();
      // void nivel3();
      // void nivel4();
      // void nivel5();

signals:
       void changedir();


};
#endif // MAINWINDOW_H
