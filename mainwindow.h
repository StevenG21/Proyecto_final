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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int v_limit;
    int h_limit;

    void keyPressEvent(QKeyEvent *event);
    MainWindow(QWidget *parent = nullptr);

    void disparar();


    ~MainWindow();

private:
    QVector<apple*> apples;
    QVector<lapiz*> pencil;
    QTimer *timer;
    QTimer *spawnapples;
    Newton *n;
    QPixmap mapascaled;

QMovie* fondo;
    QGraphicsScene *scene;
    Ui::MainWindow *ui;
public slots:
       void game();
       void generarmanzana();
       void deleteapple();
       void refresh();

};
#endif // MAINWINDOW_H
