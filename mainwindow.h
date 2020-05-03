#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QApplication>
#include <QFileDialog>
#include <graphic.h>
#include <iterator>
#include <qmath.h>
#include <QDir>
#include <QWidget>
#include <QGraphicsItem>
#include <QPixelFormat>
#include <QImage>
#include <QRandomGenerator>
#include <math.h>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QSlider>
#include <QButtonGroup>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Graphic* myGraphic;
    Graphic* myGraphic2;

    QRandomGenerator* random;
    QButtonGroup* buttGr;
    int buttNum;


    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

    void setInterfaceDisabled(bool f);

public slots:
    void setStart ();

    void getFile();
    void saveFile();


private slots:
    void on_horizontalSlider_valueChanged(int value);

    void setDerivateX ();   //получить производные
    void setDerivateY ();
    void setGradient ();    //получить градиент
    void setGauss ();    //
    void getPyramide(); //построить пирамиду

    void getMoravec ();    //оператор Моравека
    void getHarris ();    //оператор Харриса
    void getDescriptors ();    //получить дескрипторы

private:
    Ui::MainWindow *ui;

    QImage *image;
    unsigned char *grayScale;   //изображение в сером цвете

    QString path;
};

#endif // MAINWINDOW_H
