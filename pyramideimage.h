#ifndef PYRAMIDEIMAGE_H
#define PYRAMIDEIMAGE_H

#include "idoubleimage.h";
#include "doubleimagergb.h";

class PyramideImage
{
    int octaveNum;
    int layerNum;
    IDoubleImage *image;

public:
    PyramideImage(IDoubleImage *img, int octave, int layer);
    int getOctaveNum() const;
    void setOctaveNum(int value);
    int getLayerNum() const;
    void setLayerNum(int value);
    IDoubleImage *getImage() const;
    void setImage(IDoubleImage *value);
};

#endif // PYRAMIDEIMAGE_H
