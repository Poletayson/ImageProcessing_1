#ifndef DESCRIPTORCONSTRUCTOR_H
#define DESCRIPTORCONSTRUCTOR_H

#include <QDebug>
#include "interestingpoint.h"
#include "doubleimagemono.h"
#include "utils.h"


class DescriptorConstructor
{
    int w, h;
    int basketCount;    //число корзин в гистограмме
    int histogramCount;    //число гистограмм
    int gridSize;   //размер области

    double *gaussKernel;

    DoubleImageMono *dx;
    DoubleImageMono *dy;
    DoubleImageMono *gradient;
    DoubleImageMono *gradientDirection;

public:
    DescriptorConstructor(DoubleImageMono *image, int basketCountP = 8, int histCountP = 4, int gridSizeP = 16);

    Descriptor createDescriptor(InterestingPoint inputPoint);
    QList<InterestingPoint> orientPoints(QList<InterestingPoint> points);  //вычислить ориентацию особых точек
};

#endif // DESCRIPTORCONSTRUCTOR_H
