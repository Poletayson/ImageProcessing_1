#ifndef DOUBLEIMAGERGB_H
#define DOUBLEIMAGERGB_H

#include "idoubleimage.h"

#include <QImage>



class DoubleImageRGB : public IDoubleImage
{
    double *r, *g, *b;   //текущее изображение в виде матриц компонент цвета

    virtual void normalization255(double *img);
    virtual void convolutionUniversalConcrete(double *image, QList<QList<double>> core, bool norm = false);  //универсальная свертка, применяется к *image

public:
    DoubleImageRGB();
    DoubleImageRGB(QImage *image);

    virtual QImage *getImage ();    //построить изображение и вернуть
    virtual void getImage (QImage *img);    //записать матрицы в заданное изображение

    virtual void convolutionUniversal(QList<QList<double>> core, bool norm = false);  //универсальная свертка
};

#endif // DOUBLEIMAGERGB_H