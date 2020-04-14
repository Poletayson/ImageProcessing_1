#ifndef DOUBLEIMAGEMONO_H
#define DOUBLEIMAGEMONO_H

#include "idoubleimage.h"

#include <QImage>
#include <QtMath>


class DoubleImageMono : public IDoubleImage
{
    double *reserv;   //текущее изображение в виде матриц компонент цвета
    double *imageDouble;   //текущее изображение в виде матриц компонент цвета

    virtual void normalization255(double *img);
    virtual void convolutionUniversalConcrete(double *image, QList<QList<double>> core, bool norm = false);  //универсальная свертка, применяется к *image

    void setDerivateX(); //получить массивы с частными производными
    void setDerivateY();

    double *getReservCopy ();

public:
    DoubleImageMono();
    DoubleImageMono(QImage *image);

    virtual QImage *getImage ();    //построить изображение и вернуть
    virtual void getImage (QImage *img);    //записать матрицы в заданное изображение

    virtual void convolutionUniversal(QList<QList<double>> core, bool norm = false);  //универсальная свертка
    virtual void downSample(){}  //уменьшить размер в 2 раза

    void setGradient(); //получить величину градиента

    double *getImageDouble() const;
    double getPixel(int x, int y) const;    //получит значение писеля в заданной точке
};

#endif // DOUBLEIMAGEMONO_H
