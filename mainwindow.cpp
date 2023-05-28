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
    mapa = new QPixmap(":/Sprites/fondoFisica.gif");
   QPixmap mapascaled = mapa->scaled(h_limit,v_limit);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(mapascaled);
n = new Newton;

 //a = new apple;
 timer = new QTimer;

     connect(timer, SIGNAL(timeout()), scene, SLOT(update()));
     connect(timer, SIGNAL(timeout()), this, SLOT(game()));


 timer->start(10);
scene->addItem(n);





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
    cout<<apples.length()<<endl;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::game()
{

}

void MainWindow::generarmanzana()
{
    int random = QRandomGenerator::global()->bounded(800);

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

       generarmanzana();

}


        if (event->key() == Qt::Key_A) {
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
