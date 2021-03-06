#include "pyramideimage.h"

int PyramideImage::getOctaveNum() const
{
    return octaveNum;
}

void PyramideImage::setOctaveNum(int value)
{
    octaveNum = value;
}

int PyramideImage::getLayerNum() const
{
    return layerNum;
}

void PyramideImage::setLayerNum(int value)
{
    layerNum = value;
}

IDoubleImage *PyramideImage::getImage() const
{
    return image;
}

void PyramideImage::setImage(IDoubleImage *value)
{
    image = value;
}

double PyramideImage::getSigmaLocal() const
{
    return sigmaLocal;
}

void PyramideImage::setSigmaLocal(double value)
{
    sigmaLocal = value;
}

double PyramideImage::getSigmaEffective() const
{
    return sigmaEffective;
}

void PyramideImage::setSigmaEffective(double value)
{
    sigmaEffective = value;
}

PyramideImage::PyramideImage(IDoubleImage *img, int octave, int layer)
{
    octaveNum = octave;
    layerNum = layer;
    image = new DoubleImageRGB ((DoubleImageRGB*)img);
}
