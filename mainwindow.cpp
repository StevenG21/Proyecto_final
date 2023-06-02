#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QRandomGenerator>
#include <QMultimedia>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{

    efecto=false;


    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    ui->graphicsView->setMouseTracking(true);


    h_limit = 800;
    v_limit = 500;
    scene->setSceneRect(0, 0, h_limit, v_limit);
    scene->addRect(scene->sceneRect());
     ui->graphicsView->setScene(scene);


    fondo = niveles(1);
    scene->addPixmap(fondo);
n = new Newton;
scene->addItem(n);


    //

    //Nivel 1






 //a = new apple;
    timer = new QTimer;
    Tiemponivel = new QTimer;
    spawnapples = new QTimer;
    time.setHMS(0,1,0);
  //  connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
    connect(Tiemponivel, SIGNAL(timeout()), this, SLOT(cronometro()));
    connect(timer, SIGNAL(timeout()), scene, SLOT(update()));
    connect(timer, SIGNAL(timeout()), this, SLOT(game()));
    connect(spawnapples, SIGNAL(timeout()), this, SLOT(generarmanzana()));
     connect(n, SIGNAL(endframe()),this,SLOT(generarmanzana()));

 timer->start(5);
 Tiemponivel->start(1000);
 spawnapples->start(2000);






}

void MainWindow::disparar() //Esta funcion me crea los proyectiles
{
    lapiz* newpencil = new lapiz;

    newpencil->setpos(QPointF(0,450));

  //  connect(timer, SIGNAL(timeout()), newpencil, SLOT(actualizar()));
    scene->addItem(newpencil);
    pencil.push_back(newpencil);
    connect(newpencil, SIGNAL(deltepencil()), this, SLOT(deletepencil())); //Cada señal emitida es conectada a su funcion destructora.

    if(efecto==true){
        newpencil->setgravity();
    }

}

void MainWindow::deleteapple() //Elimina las manzanas
{
    apple* collidedApple = qobject_cast<apple*>(sender());
    if (collidedApple) {
        apples.removeOne(collidedApple);
        delete collidedApple;
    }
}

void MainWindow::deletepencil() //Elimina los proyectiles
{
    lapiz* collidedpencil = qobject_cast<lapiz*>(sender());
    if (collidedpencil) {
        pencil.removeOne(collidedpencil);
        delete collidedpencil;
    }
}

void MainWindow::refresh()
{

      //  this->update();

}

void MainWindow::puntaje()
{
    scene->removeItem(n);

}

void MainWindow::cronometro() //Tiempo por cada nivel
{


   ui->cronometro->setText(time.toString("m:ss"));
    time = time.addSecs(-1);


}





MainWindow::~MainWindow()
{
    delete ui;
}

QPixmap MainWindow::niveles(int x) //Selector de fondo
{
    switch (x) {
    case 1:


         movie = new QMovie(":/Sprites/fondoFisica.gif");
         movie->start();
         QApplication::processEvents();
         mapascaled = movie->currentPixmap().scaled(h_limit, v_limit);

        break;

    case 2:



        movie = new QMovie(":/Sprites/Informatica.gif");
       // movie->setSpeed(120);
        movie->start();
        mapascaled = movie->currentPixmap().scaled(h_limit, v_limit);


        break;
    }

      return mapascaled;
}

void MainWindow::game()
{
    switch (nivel) {

    case 1:

        for (lapiz* p : qAsConst(pencil)) {
                for (apple* manzana : qAsConst(apples)) {
                    if (p->collidesWithItem(manzana)) {
                        // Se ha detectado una colisión entre el lápiz y la manzana
                        cout << "Colisiona" << endl;
                        apples.removeOne(manzana); //Elimina la manzana colisionada
                        delete manzana;
                       efecto = true; //Aplica el efecto

                }
                    else{
                        efecto = false;
                    }
            }

}


        break;

    }

}

void MainWindow::generarmanzana() //Genera las manzanas
{


    int random = QRandomGenerator::global()->bounded(700);

        apple* newApple = new apple;
        newApple->setpos(QPointF(random,0));
        connect(timer, SIGNAL(timeout()), newApple, SLOT(actualizar()));//Timer para actualizar el movimiento de la manzana
        scene->addItem(newApple);
        apples.push_back(newApple);
        connect(newApple, SIGNAL(colision()), this, SLOT(deleteapple())); //Cada manzana generada emite una seña de colision

}
//Para generar las actividades a destruir copiar el mismo esquema de la clase manzana y su funcion generar.






//






void MainWindow::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_F4)
            close();
if (event->key() == Qt::Key_Space){
    disparar();

       // n->animaciones(2);

        //generarmanzana();
      //  n->animaciones(1);
}

//Movimiento del jugador
        if (event->key() == Qt::Key_A) {
            n->setpos(QPointF(n->getposx()-5,n->getposy()));
        } else if (event->key() == Qt::Key_S) {
            n->setpos(QPointF(n->getposx(),n->getposy()+5));
        } else if (event->key() == Qt::Key_D) {
           fondo = niveles(2);
           scene->update();
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

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    QPointF pos = event->pos();

    qDebug() << event->pos();

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
 qDebug() << event->GraphicsSceneMousePress;
}

