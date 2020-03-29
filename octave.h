#ifndef OCTAVE_H
#define OCTAVE_H

#include "doubleimagergb.h"
#include "doubleimagemono.h"
#include "idoubleimage.h"
#include "pyramideimage.h"

//одна октава, содержит список слоев
class Octave
{
    QList<PyramideImage*> *layers;
    int octave;

public:
    Octave(QList<PyramideImage*> *list, int octavePar);
    ~Octave();
    QList<PyramideImage *> *getLayers() const;
    void setLayers(QList<PyramideImage *> *value);
    int getOctave() const;
    void setOctave(int value);
};

#endif // OCTAVE_H
