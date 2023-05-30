#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QRandomGenerator>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new QGraphicsScene(this);
    h_limit = 800;
    v_limit = 500;
    scene->setSceneRect(0,0,h_limit,v_limit);
    scene->addRect(scene->sceneRect());
    fondo = new QMovie(":/Sprites/fondoFisica.gif");
    fondo->start();
   mapascaled = fondo->currentPixmap().scaled(h_limit,v_limit);
   scene->addPixmap(mapascaled);
    ui->graphicsView->setScene(scene);


n = new Newton;

 //a = new apple;
 timer = new QTimer;
 spawnapples = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));

     connect(timer, SIGNAL(timeout()), scene, SLOT(update()));
     connect(spawnapples, SIGNAL(timeout()), this, SLOT(game()));
     connect(n, SIGNAL(endframe()),this,SLOT(generarmanzana()));

 timer->start(8);
 //spawnapples->start(4000);
scene->addItem(n);





}

void MainWindow::disparar()
{
    lapiz* newpencil = new lapiz;
    newpencil->setpos(QPointF(0,450));

  //  connect(timer, SIGNAL(timeout()), newpencil, SLOT(actualizar()));
    scene->addItem(newpencil);
    pencil.push_back(newpencil);

}

void MainWindow::deleteapple()
{
    apple* collidedApple = qobject_cast<apple*>(sender());

    if (collidedApple) {
        apples.removeOne(collidedApple);
        delete collidedApple;
         // Quitar el objeto de la escena
       // Eliminar el objeto del vector apples
        // Liberar la memoria del objeto
    }
   // cout<<apples.length()<<endl;


}

void MainWindow::refresh()
{
  //  mapascaled = fondo->currentPixmap().scaled(h_limit,v_limit);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::game()
{
n->animaciones(2);

}

void MainWindow::generarmanzana()
{


    int random = QRandomGenerator::global()->bounded(700);

        apple* newApple = new apple;
        newApple->setpos(QPointF(random,0));
        connect(timer, SIGNAL(timeout()), newApple, SLOT(actualizar()));
        scene->addItem(newApple);
        apples.push_back(newApple);
        connect(newApple, SIGNAL(colision()), this, SLOT(deleteapple()));

}







void MainWindow::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_F4)
            close();
if (event->key() == Qt::Key_Space){

        n->animaciones(2);

        //generarmanzana();
      //  n->animaciones(1);

}


        if (event->key() == Qt::Key_A) {
            disparar();
            n->setpos(QPointF(n->getposx()-5,n->getposy()));
        } else if (event->key() == Qt::Key_S) {
            n->setpos(QPointF(n->getposx(),n->getposy()+5));
        } else if (event->key() == Qt::Key_D) {
            n->setpos(QPointF(n->getposx()+5,n->getposy()));
        } else if (event->key() == Qt::Key_W) {
        n->setpos(QPointF(n->getposx(),n->getposy()-5));
        } else if (event->key() == Qt::Key_M) {//pause
            if (timer->isActive())
                timer->stop();
            else
                timer->start(10);
        }





}
