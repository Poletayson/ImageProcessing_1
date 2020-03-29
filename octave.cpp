#include "octave.h"

QList<PyramideImage *> *Octave::getLayers() const
{
    return layers;
}

void Octave::setLayers(QList<PyramideImage *> *value)
{
    layers = value;
}


Octave::Octave(QList<PyramideImage *> *list, int octavePar)
{
    layers = list;
    octave = octavePar;
}

int Octave::getOctave() const
{
    return octave;
}

void Octave::setOctave(int value)
{
    octave = value;
}

Octave::~Octave()
{
    //удаляем слои
    for (int var = 0; var < layers->count(); ++var) {
        delete (*layers)[var];
    }
    layers->clear();
    delete layers;
}
