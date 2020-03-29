#ifndef PYRAMIDEIMAGE_H
#define PYRAMIDEIMAGE_H

#include "idoubleimage.h";
#include "doubleimagergb.h";

class PyramideImage
{
    int octaveNum;
    int layerNum;
    IDoubleImage *image;

    double sigmaLocal;
    double sigmaEffective;

public:
    PyramideImage(IDoubleImage *img, int octave, int layer);
    int getOctaveNum() const;
    void setOctaveNum(int value);
    int getLayerNum() const;
    void setLayerNum(int value);
    IDoubleImage *getImage() const;
    void setImage(IDoubleImage *value);
    double getSigmaLocal() const;
    void setSigmaLocal(double value);
    double getSigmaEffective() const;
    void setSigmaEffective(double value);
};

#endif // PYRAMIDEIMAGE_H
