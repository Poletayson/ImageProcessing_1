#ifndef UTILS_H
#define UTILS_H

#include "math.h"
#include "descriptor.h"
#include <QImage>
#include <QPixmap>
#include <QPainter>

class Utils
{
public:
    Utils();

    static double getDistance(double x0, double y0, double x1, double y1);  //расстояние между точками
    static double getDescriptorDistance(Descriptor d1, Descriptor d2);  //расстояние между дескрипторами
    static QImage imageJoining (QImage i1, QImage i2);
};

#endif // UTILS_H
