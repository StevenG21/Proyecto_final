#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QRandomGenerator>
//#include <QMultimedia>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    nivel=1;
    puntos = 0;
    angulo = 90;
    ampl= 25;
    frec = 0.6;
    potencia = 0;
    gravity = 2.5;
//pointerpen = new lapiz;
     gif = new QGraphicsPixmapItem;
     nivel1theme= new QMediaPlayer;
     s1 = new QMediaPlayer;
     as = new QSoundEffect;
     as->setSource(QUrl("qrc:/Sonidos/applesound.wav"));
   s1->setMedia(QMediaContent(QUrl("qrc:/Sonidos/soundbook.mp3")));
   bookcounter = 0;
    efecto=false;
    ui->setupUi(this);

    h_limit = 800;
    v_limit = 500;
//QTimer timer2;
//tdisparo = new QTimer;
//connect(tdisparo, SIGNAL(timeout()), this, SLOT(power()));
  t = 0;
  Colitime = new QTimer;
    timerbooks = new QTimer;
    timer = new QTimer;
    Tiemponivel = new QTimer;
    spawnapples = new QTimer;
    time.setHMS(0,1,0);
  //  connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
    connect(Tiemponivel, SIGNAL(timeout()), this, SLOT(cronometro()));
    connect(timerbooks, SIGNAL(timeout()), this, SLOT(generarlibro()));
    connect(Colitime, SIGNAL(timeout()), this, SLOT(game()));
    connect(spawnapples, SIGNAL(timeout()), this, SLOT(spawn()));

  //  connect(ui->graphicsView,SIGNAL(mousePressEvent()),this, SLOT(handleMousePressEvent()));

newscene(1);
}

void MainWindow::disparar(float x,float y,int vel) //Esta funcion me crea los proyectiles
{
    lapiz* newpencil = new lapiz;

    newpencil->setpos(QPointF(x,y));
    newpencil->setangle(angulo);
    newpencil->setgravity(gravity);
    newpencil->dir_pencil();

  //  connect(timer, SIGNAL(timeout()), newpencil, SLOT(actualizar()));
    scene->addItem(newpencil);
    pencil.push_back(newpencil);
    connect(timer, SIGNAL(timeout()),newpencil, SLOT(actualizar())); //Movimiento
    connect(newpencil, SIGNAL(deltepencil()), this, SLOT(deletepencil())); //Cada señal emitida es conectada a su funcion destructora.


}

void MainWindow::deleteapple() //Señal para eliminar manzanas
{

    apple* collidedApple = qobject_cast<apple*>(sender());
    if (collidedApple) {
        apples.removeOne(collidedApple);
        delete collidedApple;
    }
}

void MainWindow::deletebook()// Elimina los libros
{
    actividad* collidedbook = qobject_cast<actividad*>(sender());
    if(collidedbook){
        books.removeOne(collidedbook);
        delete collidedbook;
    }
}

void MainWindow::deletepencil() //Elimina los proyectiles que emitieron la señal
{
    lapiz* collidedpencil = qobject_cast<lapiz*>(sender());
    if (collidedpencil) {
        pencil.removeOne(collidedpencil);
        delete collidedpencil;
    }
}

void MainWindow::refresh()
{

    mapascaled = movie->currentPixmap().scaled(h_limit, v_limit);
    gif->setPixmap(mapascaled);
}

void MainWindow::spawn()
{
  n->animaciones(2);

}

void MainWindow::cronometro() //Tiempo por cada nivel
{


    if(time.toString("m:ss") == "0:00"){

        bookcounter = 0;
        qDebug() << "Se acabo el tiempo";
     timer-> stop();
     disconnect(timer, SIGNAL(timeout()), scene, SLOT(update()));
     scene->removeItem(gif);

        ui->nivelname->setHidden(false);
        ui->nota->setHidden(false);
        ui->textonota->setHidden(false);
        Tiemponivel->stop();
        spawnapples->stop();
        timerbooks->stop();
        Colitime->stop();
        timer->stop();
        delete jugador;
        delete scene;
        delete movie;
    //    delete n;
        time.setHMS(0,1,0);
        ui->nivelname->setText(nombrenivel);
        QString nota = QString::number(puntos);
        ui->nota->setText(nota);
        nivel ++;

    }
    time = time.addSecs(-1);
    ui->cronometro->setText(time.toString("m:ss"));
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
         mapascaled = movie->currentPixmap().scaled(h_limit, v_limit);
         gif->setPixmap(mapascaled);
        break;

    case 2:
        movie = new QMovie(":/Sprites/Informatica.gif");
        movie->start();
       // movie->setSpeed(120);
      //  movie->start();
        mapascaled = movie->currentPixmap().scaled(h_limit, v_limit);
        gif->setPixmap(mapascaled);
        break;
    }
    return mapascaled;
}

void MainWindow::newscene(int x )
{
    apples.clear();
    books.clear();
    pencil.clear();
    nivel = x;
    tru=false;
    jugador = new player;
    fondo = niveles(x);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, h_limit, v_limit);
    scene->addRect(scene->sceneRect());
    ui->graphicsView->setScene(scene);
    scene->addItem(gif);
    n = new Newton;
    scene->addItem(n);
    connect(n, SIGNAL(endframe()), this, SLOT(generarmanzana()));
    scene->setFocus();
    connect(timer, SIGNAL(timeout()), scene, SLOT(update()));
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
    timer->start(3);
    ui->nivelname->setHidden(true);
    ui->nota->setHidden(true);
    ui->textonota->setHidden(true);
    Colitime->start(2);

    if(x == 1){
        nombrenivel = "Fisica";
        time.setHMS(0,1,0);
        numlibros=30;
        this->setporcentaje(0.1666667);
        nivel1theme->setMedia(QMediaContent(QUrl("qrc:/Sonidos/physics theme.mp3")));
        nivel1theme->play();
        jugador->setPos(100,425);
        scene->addItem(jugador);
        timerbooks->start(1000);
        Tiemponivel->start(1000);
        spawnapples->start(3000);

    }

    if(x == 2){
        puntos=0;

        nivel1theme->stop();
        n->animaciones(3);
        nombrenivel = "Informatica";
        time.setHMS(0,1,0);
        numlibros=40;
        this->setporcentaje(0.125);
        gravity = 2;
        nivel1theme->setMedia(QMediaContent(QUrl("qrc:/Sonidos/Informaticatheme.mp3")));
        nivel1theme->play();
        jugador->setPos(100,425);
        scene->addItem(jugador);
        timerbooks->start(800);
        Tiemponivel->start(1000);
       // spawnapples->start(3000);
    }
    this->update();
}

void MainWindow::setporcentaje(float p)
{
    porcentaje=p;
    this->update();
}

void MainWindow::power()
{
    potencia = ampl * sin(frec * t) + ampl;

t += 0.05;

}

void MainWindow::game()
{
   for(lapiz* p2 : qAsConst(pencil)) {
    for (actividad* libro : qAsConst(books)) {
        if (p2->collidesWithItem(libro)) {
            if(books.removeOne(libro)){

                delete libro;
           }
    gravity -=0.1;


            s1->play();


             puntos += porcentaje; // Puntos

             }
}
        }

    switch (nivel) {
    case 1:
                for (apple* manzana : qAsConst(apples)) {
                    if(jugador->collidesWithItem(manzana)){
                        emit manzana->colision();
                         as->play();
                          gravity +=0.5;
                    }

                      }
        break;

    case 2:
        break;
    }

    if(puntos>=4.9 && tru==false){

        Tiemponivel->start(200);
        tru=true;

    }

}

void MainWindow::generarmanzana() //Genera las manzanas
{
   // int random = QRandomGenerator::global()->bounded(700);
    apple* newApple = new apple;
    newApple->setpos(QPointF(jugador->getposx()+100,0));
        connect(timer, SIGNAL(timeout()), newApple, SLOT(actualizar()));//Timer para actualizar el movimiento de la manzana
        scene->addItem(newApple);
        apples.push_back(newApple);
        connect(newApple, SIGNAL(colision()), this, SLOT(deleteapple())); //Cada manzana generada emite una seña de colision

}

void MainWindow::generarlibro()
{
 if(bookcounter>=numlibros){
  timerbooks->stop();

 }
 if(bookcounter<numlibros){
    actividad* newbook = new actividad;
    newbook->setPos(0,150);
    connect(timer, SIGNAL(timeout()), newbook, SLOT(movimiento()));
    connect(newbook, SIGNAL(deletebook()), this, SLOT(deletebook()));
    scene->addItem(newbook);
    books.push_back(newbook);
}
    bookcounter += 1;
}
//Para generar las actividades a destruir copiar el mismo esquema de la clase manzana y su funcion generar.



void MainWindow::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_F4)
            close();
if (event->key() == Qt::Key_Space){

disparar(jugador->getposx()+100,jugador->getposy(),potencia);
       // n->animaciones(2);

        //generarmanzana();
      //  n->animaciones(1);
}

if(event->key()== Qt::Key_Return){
    newscene(nivel);
}

//Movimiento del jugador
        if (event->key() == Qt::Key_A) {

          jugador->setpos(QPointF(jugador->getposx()-8,jugador->getposy()));
            jugador->sprite(2);
        } else if (event->key() == Qt::Key_S) {
    angulo -= 2;


        } else if (event->key() == Qt::Key_D) {


          jugador->setpos(QPointF(jugador->getposx()+8,jugador->getposy()));
          jugador->sprite(1);
        } else if (event->key() == Qt::Key_W) {
      angulo += 2;

        } else if (event->key() == Qt::Key_M) {//pause
            if (timer->isActive())
                timer->stop();
            else
                timer->start(2);
        }

jugador->update();
scene->update();
qDebug() << angulo;


}



