#include "descriptor.h"

void Descriptor::normalize()
{
    double size = 0;
    for (double x : histograms)
        size += x * x;
    size = sqrt(size);

    for(int i = 0; i < histograms.size(); i++){
        if(histograms[i] / size > 0.2) {
            histograms[i] = 0.2;
        } else {
            histograms[i] = histograms[i]/size;
        }
    }

    //еще раз
    size = 0;
    for (double x : histograms)
        size += x * x;
    size = sqrt(size);

    for(int i = 0; i < histograms.size(); i++){
        histograms[i] = histograms[i] / size;
    }
}

QList<double> Descriptor::getHistograms() const
{
    return histograms;
}

void Descriptor::setHistograms(const QList<double> &value)
{
    histograms = value;
}

int Descriptor::getBascketCount() const
{
    return bascketCount;
}

void Descriptor::setBascketCount(int value)
{
    bascketCount = value;
}

int Descriptor::getHistogramsCount() const
{
    return histogramsCount;
}

void Descriptor::setHistogramsCount(int value)
{
    histogramsCount = value;
}

QString Descriptor::toString()
{
    QString str = "";
    for (int i = 0; i < histograms.size(); i++)
        str += QString(" ") + QString::number(histograms[i], 'f');
    return str;
}

Descriptor::Descriptor(int bascketCountP, int histogramsCountP)
{
    bascketCount = bascketCountP;
    histogramsCount = histogramsCountP;
    //заполняем гистограммы нулями
    for (int i = 0, endI = bascketCount * histogramsCount * bascketCount * histogramsCount; i < endI; i++){
        histograms.append(0);
    }
}

Descriptor::Descriptor()
{
    bascketCount = 0;
    histogramsCount = 0;
}

double Descriptor::getBin(int hist, int bin)
{
    return histograms[hist * bascketCount + bin];
}

void Descriptor::setBin(int hist, int bin, double value)
{
//    qDebug() << hist << " " << bin << " " << value << " size: " << histograms.count();
    histograms[hist * bascketCount + bin] = value;
}
