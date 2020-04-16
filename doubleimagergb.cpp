#include "doubleimagergb.h"

void DoubleImageRGB::normalization255(double *img)
{
    double min = 0, max = 1;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (min > img[j * width + i])
                min = img[j * width + i];
            if (max < img[j * width + i])
                max = img[j * width + i];
        }
    }



    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            img[j * width + i] = (img[j * width + i] - min) * (255 - 0) / (max - min) + 0;
        }
    }
}

void DoubleImageRGB::convolutionUniversalConcrete(double *image, QList<QList<double> > core, bool norm)
{
    //списки в ядре располагаются по горизонтали, поэтому размеры берутся так а не иначе
        int coreW = static_cast<int>(core[0].count() / 2);
        int coreH = static_cast<int>(core.count() / 2);

        int widthWorking = width + coreW * 2;    //ширина и высота расширенного, рабочего изображения
        int heightWorking = height + coreH * 2;

        //расширяем изображение на размер ядра
        double *imageWorking = new double [widthWorking * heightWorking]; //расширенное рабочее изображение

        //Заполняем рабочее изображение
        for (int j = 0; j < heightWorking; ++j) //все строки
            for (int i = 0; i < widthWorking; ++i) {
                //Здесь мы просто точки, лежащие за границей, приравниваем граничным =)
                imageWorking[j * widthWorking + i] = image[(j - coreH <= 0 ? 0 : (j >= height - 1 ? height - 1 : j - coreH)) * width +
                        (i - coreW <= 0 ? 0 : (i >= width - 1 ? width - 1 : i - coreW))];
            }

        int xSize = core[0].count();
        int ySize = core.count();

        //вычисляем сумму элементов ядра
        double coreSum = 0;
        if (norm)   //если нормируем
            for (int x = 0; x < xSize; ++x) {
                for (int y = 0; y < ySize; ++y) {
                    coreSum += core[y][x];
                }
            }



        //применяем свертку ко всем точкам
        for (int j = 0; j < height; ++j) //все строки
            for (int i = 0; i < width; ++i) {
                double sum = 0; //результат свертки для одной точки

                for (int u = 0; u < ySize; u++)//для каждого ряда в ядре
                    for (int v = 0; v < xSize; v++)  //для каждого значения в ряду
                        sum += imageWorking[(j - u + ySize - 1) * widthWorking + (i - v + xSize - 1)] * core[u][v]; //здесь учитываем что coreW == (core[0].count() - 1) / 2, coreH аналогично
    //imageWorking[(j + u) * widthWorking + (i + v)] * core[u][v]
                if (norm)
                    image[j * width + i] = sum / coreSum;
                else
                    image[j * width + i] = sum;
            }
}

void DoubleImageRGB::downSample()  //уменьшить размер в 2 раза
{
    int w = width;
    int h = height;
    width = width / 2;
    height = height / 2;

    double *rOld = r;
    double *gOld = g;
    double *bOld = b;

    r = new double [height * width];
    g = new double [height * width];
    b = new double [height * width];

    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++){
            r[j * width + i] = rOld[j * 2 * w + i * 2];
            g[j * width + i] = gOld[j * 2 * w + i * 2];
            b[j * width + i] = bOld[j * 2 * w + i * 2];
        }

    delete [] rOld;
    delete [] gOld;
    delete [] bOld;
}

void DoubleImageRGB::setPixel(int x, int y, double r, double g, double b)
{
    if (x >= 0 && x < width && y > 0 && y <height){
        (this->r)[y * width + x] = r;
        (this->g)[y * width + x] = g;
        (this->b)[y * width + x] = b;
    }
}

DoubleImageRGB::DoubleImageRGB()
{

}

DoubleImageRGB::DoubleImageRGB(QImage *image)
{
    width = image->width();
    height = image->height();

    QRgb *imageBytes[height];
    //построчно сканируем изображение
    for (int i = 0; i < height; i++){
        imageBytes[i] = (QRgb*)(image->scanLine(i));
    }

    r = new double [height * width];
    g = new double [height * width];
    b = new double [height * width];

    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++){
            r[j * width + i] = static_cast<double>(qRed(imageBytes[j][i])) / 255;
            g[j * width + i] = static_cast<double>(qGreen(imageBytes[j][i])) / 255;
            b[j * width + i] = static_cast<double>(qBlue(imageBytes[j][i])) / 255;
        }
}

DoubleImageRGB::DoubleImageRGB(DoubleImageRGB *image)
{
    width = image->width;
    height = image->height;

    r = new double [height * width];
    g = new double [height * width];
    b = new double [height * width];
    double *ptrR = ((DoubleImageRGB*)image)->r;
    double *ptrG = ((DoubleImageRGB*)image)->g;
    double *ptrB = ((DoubleImageRGB*)image)->b;

    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++){
            r[j * width + i] = ptrR[j * width + i];
            g[j * width + i] = ptrG[j * width + i];
            b[j * width + i] = ptrB[j * width + i];
        }
}

QImage *DoubleImageRGB::getImage()
{
    QRgb *imageBytes[height];

    QImage *img = new QImage (width, height, QImage::Format_RGB32);

    //построчно сканируем изображение
    for (int i = 0; i < height; i++){
        imageBytes[i] = (QRgb*)(img->scanLine(i));
    }

    normalization255(r);
    normalization255(g);
    normalization255(b);
    //устанавливаем значения для изображения
    for (int j = 0; j < height; ++j) //все строки
        for (int i = 0; i < width; ++i) {
            imageBytes[j][i] = qRgb(static_cast<int>(r[j * width + i]), static_cast<int>(g[j * width + i]), static_cast<int>(b[j * width + i]));
        }

    return img;
}

void DoubleImageRGB::getImage(QImage *img)
{
    QRgb *imageBytes[height];
    //построчно сканируем изображение
    for (int i = 0; i < height; i++){
        imageBytes[i] = (QRgb*)(img->scanLine(i));
    }

    normalization255(r);
    normalization255(g);
    normalization255(b);
    //устанавливаем значения для изображения
    for (int j = 0; j < height; ++j) //все строки
        for (int i = 0; i < width; ++i) {
            imageBytes[j][i] = qRgb(static_cast<int>(r[j * width + i]), static_cast<int>(g[j * width + i]), static_cast<int>(b[j * width + i]));
        }
}

void DoubleImageRGB::convolutionUniversal(QList<QList<double> > core, bool norm)
{
    convolutionUniversalConcrete(r, core, norm);
    convolutionUniversalConcrete(g, core, norm);
    convolutionUniversalConcrete(b, core, norm);
}

double *DoubleImageRGB::getColorMatrix(int colNum)
{
    switch (colNum) {
    case 1:
        return r;
    case 2:
        return g;
    case 3:
        return b;
    default:
        return nullptr;
    }
}
