#include "doubleimagemono.h"

double *DoubleImageMono::getImageDouble() const
{
    return imageDouble;
}

double DoubleImageMono::getPixel(int x, int y) const //получит значение писеля в заданной точке
{
    switch (effect) {
        case EDGE_COPY:{
            int i, j;
            i = x <= 0 ? 0 : (x >= width - 1 ? width - 1 : x);
            j = y <= 0 ? 0 : (y >= height - 1 ? height - 1 : y);
            return imageDouble[j * width + i];
        }
        case EDGE_BLACK:{
            if (x >= 0 && x <= width - 1 && y >= 0 && y <= height - 1)
                return imageDouble[y * width + x];
            else return 0;

        }
    }
    int i, j;
    i = x <= 0 ? 0 : (x >= width - 1 ? width - 1 : x);
    j = y <= 0 ? 0 : (y >= height - 1 ? height - 1 : y);
    return imageDouble[j * width + i];
}

void DoubleImageMono::setPixel(int x, int y, double c)
{
    if (x >= 0 && x < width && y > 0 && y <height)
        (this->imageDouble)[y * width + x] = c;
}

void DoubleImageMono::save(QString name)
{
    normalization255(imageDouble);
    QString path = QApplication::applicationDirPath() + "/Input/" + name;      //текущая директория
    getImage()->save(path);
}

void DoubleImageMono::setEffect(const EdgeEffects &value)
{
    effect = value;
}

void DoubleImageMono::normalization255(double *img)
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

void DoubleImageMono::convolutionUniversalConcrete(double *image, QList<QList<double> > core, bool norm)
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

DoubleImageMono::DoubleImageMono()
{
    reserv = nullptr;
    imageDouble = nullptr;
    effect = EDGE_COPY; //по умолчанию
}

DoubleImageMono::DoubleImageMono(QImage *image)
{
    width = image->width();
    height = image->height();

    QRgb *imageBytes[height];
    //построчно сканируем изображение
    for (int i = 0; i < height; i++){
        imageBytes[i] = (QRgb*)(image->scanLine(i));
    }

    imageDouble = new double [height * width];
    reserv = new double [height * width];

    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++){
            imageDouble[j * width + i] = static_cast<double>(qRed(imageBytes[j][i])) / 255;
            reserv[j * width + i] = static_cast<double>(qRed(imageBytes[j][i])) / 255;
        }

    effect = EDGE_COPY; //по умолчанию
}

//конструктор копирования на основе массива
DoubleImageMono::DoubleImageMono(double *image, int w, int h)
{
    width = w;
    height = h;

    imageDouble = new double [height * width];
    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++){
            imageDouble[j * width + i] = image[j * width + i];
        }

    effect = EDGE_COPY; //по умолчанию
}

QImage *DoubleImageMono::getImage()
{
    QRgb *imageBytes[height];

    QImage *img = new QImage (width, height, QImage::Format_RGB32);

    //построчно сканируем изображение
    for (int i = 0; i < height; i++){
        imageBytes[i] = (QRgb*)(img->scanLine(i));
    }

    normalization255(imageDouble);

    //устанавливаем значения для изображения
    for (int j = 0; j < height; ++j) //все строки
        for (int i = 0; i < width; ++i) {
            imageBytes[j][i] = qRgb(static_cast<int>(imageDouble[j * width + i]), static_cast<int>(imageDouble[j * width + i]), static_cast<int>(imageDouble[j * width + i]));
        }

    return img;
}

void DoubleImageMono::getImage(QImage *img)
{
    QRgb *imageBytes[height];
    //построчно сканируем изображение
    for (int i = 0; i < height; i++){
        imageBytes[i] = (QRgb*)(img->scanLine(i));
    }

    normalization255(imageDouble);

    //устанавливаем значения для изображения
    for (int j = 0; j < height; ++j) //все строки
        for (int i = 0; i < width; ++i) {
            imageBytes[j][i] = qRgb(static_cast<int>(imageDouble[j * width + i]), static_cast<int>(imageDouble[j * width + i]), static_cast<int>(imageDouble[j * width + i]));
        }
}

void DoubleImageMono::convolutionUniversal(QList<QList<double> > core, bool norm)
{
    convolutionUniversalConcrete(imageDouble, core, norm);
}

void DoubleImageMono::setDerivateX()
{
    QList<QList<double> > core; //ядро свертки
    core.append(QList<double>({1, 0, -1}));
    core.append(QList<double>({2, 0, -2}));
    core.append(QList<double>({1, 0, -1}));

    convolutionUniversal(core); //непосредственно вычисляем
}

void DoubleImageMono::setDerivateY()
{
    QList<QList<double> > core; //ядро свертки
    core.append(QList<double>({1, 2, 1}));
    core.append(QList<double>({0, 0, 0}));
    core.append(QList<double>({-1, -2, -1}));

    convolutionUniversal(core); //непосредственно вычисляем
}

double *DoubleImageMono::getReservCopy()
{
    //копируем
    double *cp = new double[width * height];
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            cp[j * width + i] = imageDouble[j * width + i];
        }
    }
    return cp;
}

void DoubleImageMono::setGradient()
{
    setDerivateX(); //получаем производную по X


    double *derivateX = imageDouble;
    imageDouble = getReservCopy();  //копируем

    setDerivateY(); //получаем производную по Y


    //считаем величину градиента
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            imageDouble[j * width + i] = sqrt(imageDouble[j * width + i] * imageDouble[j * width + i] +
                    derivateX[j * width + i] * derivateX[j * width + i]);
        }
    }
    delete [] derivateX;
}
