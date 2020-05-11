#ifndef DOUBLEIMAGEMONO_H
#define DOUBLEIMAGEMONO_H

#include "idoubleimage.h"

#include <QApplication>
#include <QImage>
#include <QtMath>


class DoubleImageMono : public IDoubleImage
{
public:
    enum EdgeEffects{EDGE_COPY, EDGE_BLACK};

private:
    double *reserv;   //текущее изображение в виде матриц компонент цвета
    double *imageDouble;   //текущее изображение в виде матриц компонент цвета

    EdgeEffects effect;

    virtual void normalization255(double *img);
    virtual void convolutionUniversalConcrete(double *image, QList<QList<double>> core, bool norm = false);  //универсальная свертка, применяется к *image

    double *getReservCopy ();

public:
    DoubleImageMono();
    DoubleImageMono(QImage *image);
    DoubleImageMono(double *image, int w, int h);   //конструктор копирования на основе массива

    virtual QImage *getImage ();    //построить изображение и вернуть
    virtual void getImage (QImage *img);    //записать матрицы в заданное изображение

    virtual void convolutionUniversal(QList<QList<double>> core, bool norm = false);  //универсальная свертка
    virtual void downSample(){}  //уменьшить размер в 2 раза

    void setDerivateX(); //получить массивы с частными производными
    void setDerivateY();
    void setGradient(); //получить величину градиента

    double *getImageDouble() const;

    double getPixel(int x, int y) const;    //получит значение писеля в заданной точке
    void setPixel (int x, int y, double c);

    void save (QString name);
    void setEffect(const EdgeEffects &value);
};

#endif // DOUBLEIMAGEMONO_H
