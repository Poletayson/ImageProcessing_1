#ifndef IDOUBLEIMAGE_H
#define IDOUBLEIMAGE_H

#include <QImage>



class IDoubleImage
{
public:
    virtual QImage *getImage () = 0;    //построить изображение и вернуть
    virtual void getImage (QImage *IMG) = 0;    //записать матрицы в заданное изображение

    virtual void convolutionUniversal(QList<QList<double>> core, bool norm = false) = 0;  //универсальная свертка, применяется к *image
    virtual void downSample() = 0;  //уменьшить размер в 2 раза

protected:
    int width;
    int height;

    virtual void normalization255(double *img) = 0;

};

#endif // IDOUBLEIMAGE_H
