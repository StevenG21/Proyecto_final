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
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int v_limit;
    int h_limit;
void generarmanzana();
    void keyPressEvent(QKeyEvent *event);
    MainWindow(QWidget *parent = nullptr);



    ~MainWindow();

private:
    QVector<apple*> apples;
    QTimer *timer;
    Newton *n;
QPixmap* mapa;
    QGraphicsScene *scene;
    Ui::MainWindow *ui;
public slots:
       void game();
     void deleteapple();

};
#endif // MAINWINDOW_H
