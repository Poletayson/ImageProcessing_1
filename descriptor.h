#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include "math.h"
#include <QList>
#include <QDebug>


class Descriptor
{
    int bascketCount;   //число корзин в одной гистограмме
    int histogramsCount;   //число гистограмм
    QList <double> histograms;

public:
    Descriptor(int bascketCountP, int histogramsCountP);
    Descriptor();

    void normalize();

    double getBin (int hist, int bin);
    void setBin (int hist, int bin, double value);
    QList<double> getHistograms() const;
    void setHistograms(const QList<double> &value);
    int getBascketCount() const;
    void setBascketCount(int value);
    int getHistogramsCount() const;
    void setHistogramsCount(int value);

    QString toString ();
};

#endif // DESCRIPTOR_H
