#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "idoubleimage.h"

#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <qlist.h>
#include <QPixelFormat>
#include <QImage>
#include <QPainter>
#include <QtMath>
#include <QRect>
#include "doubleimagergb.h"
#include "doubleimagemono.h"
#include "idoubleimage.h"
#include "pyramideimage.h"
#include "octave.h"
#include <QDebug>
#include <QPainter>
#include <QFile>

class Graphic : public QGraphicsView
{
    Q_OBJECT
public:
   QGraphicsScene* myScene;

   qreal SIGMA;
   QPen *p;


signals:
    void ResizeSignal ();

public:
    QGraphicsPixmapItem *imageItem;
    QGraphicsPixmapItem *reserve;
    int counter = 0;
    explicit Graphic(QWidget *parent = nullptr);
    void clear ();      //очистить
    void ClearItem (QGraphicsItemGroup* Items);
    void GetFileImage (QString file);
                   //отрисовка
    QGraphicsItemGroup* addRect (qreal x, qreal y, qreal w, qreal h, QPen* p, QGraphicsScene* sc);


//    QColor matrixColorMul (QColor colors[3][3], int matrix[3][3]);
//    QRgb matrixColorMul (QRgb colors[3][3], int matrix[3][3]);
//    unsigned char matrixMul (unsigned char channel[3][3], int matrix[3][3]);
//    QColor colorNormir (QColor colorX, QColor colorY);
//    QRgb colorNormir (QRgb colorX, QRgb colorY);
//    unsigned char componentNormir (unsigned char colorX, unsigned char colorY);



    QImage *getImage() const;
    void setImage(QImage *value);


    void setImageDouble (); //установить текущее изображение в виде матрицы double, чтобы с ним можно было производить манипуляции
    void setImageFromDouble (); //установить текущее изображение из матрицы double
    void setImageFromRGB (); //установить текущее изображение из матриц цветов

//    void setGray ();    //установить значения интенсивности
//    void setRGB ();    //установить значения цветов

    void convolutionUniversal(double *image, int w, int h, QList<QList<double>> core, bool norm = false);  //универсальная свертка, применяется к *image
    void setDerivateX(); //получить массивы с частными производными
    void setDerivateY();
    void setGradient(); //получить величину градиента
    void gaussianFilter(double sigma);
    void gaussianFilterRGB(double sigma);
    void gaussianFilterRGBSep(double sigma);

    void getPyramide(int octaveCount, int levelCount, double sigmaA, double sigma0); //построить пирамиду
    double getL(QList<Octave*> pyramide, int y, int x, double sigma, int colorNum); //функция L(x, y, sigma)

    void setLIMIT(int value);

public slots:
    //void Drawing ();
private:
    int LIMIT = 225;

    QImage *image;
    QList<Octave*> pyramide;    //пирамида, состоящая из октав

    IDoubleImage *imageRGB, *imageMono;


};

#endif // GRAPHIC_H
