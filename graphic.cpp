#include "graphic.h"



Graphic::Graphic(QWidget *parent) : QGraphicsView(parent)
{
    this->setAlignment(Qt::AlignCenter);        //выравнивание по центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    image = nullptr;
    imageItem = nullptr;
    reserve = nullptr;
    imageRGB = nullptr;
    imageMono = nullptr;
    myScene = new QGraphicsScene ();
    this->setScene(myScene);

    SIGMA = 0.8;
}


void Graphic::ClearItem (QGraphicsItemGroup* Items)
{
    foreach (QGraphicsItem* items, myScene->items(Items->boundingRect()))
        if (items->group() == Items)
            delete items;
}

void Graphic::GetFileImage (QString file)
{
    if (!imageItem)
        delete (imageItem);
    image = new QImage (file);                        //картинка
    imageItem = myScene->addPixmap(QPixmap::fromImage(*image));   //добавляем пиксмап и получаем итем
    myScene->setSceneRect(0, 0, image->width(), image->height());   //размер сцены под картинку
}



//QColor Graphic::matrixColorMul(QColor colors[3][3], int matrix[3][3])
//{
//    int r = 0, g = 0, b = 0;
//    r = colors[0][0].red() * matrix[0][0] + colors[0][1].red() * matrix[0][1] + colors[0][2].red() * matrix[0][2] +
//            colors[1][0].red() * matrix[1][0] + colors[1][1].red() * matrix[1][1] + colors[1][2].red() * matrix[1][2] +
//            colors[2][0].red() * matrix[2][0] + colors[2][1].red() * matrix[2][1] + colors[2][2].red() * matrix[2][2];
//    g = colors[0][0].green() * matrix[0][0] + colors[0][1].green() * matrix[0][1] + colors[0][2].green() * matrix[0][2] +
//            colors[1][0].green() * matrix[1][0] + colors[1][1].green() * matrix[1][1] + colors[1][2].green() * matrix[1][2] +
//            colors[2][0].green() * matrix[2][0] + colors[2][1].green() * matrix[2][1] + colors[2][2].green() * matrix[2][2];
//    b = colors[0][0].blue() * matrix[0][0] + colors[0][1].blue() * matrix[0][1] + colors[0][2].blue() * matrix[0][2] +
//            colors[1][0].blue() * matrix[1][0] + colors[1][1].blue() * matrix[1][1] + colors[1][2].blue() * matrix[1][2] +
//            colors[2][0].blue() * matrix[2][0] + colors[2][1].blue() * matrix[2][1] + colors[2][2].blue() * matrix[2][2];
//    r = qMax (0,
//              qMin (r, 255));
//    g = qMax (0,
//              qMin (g, 255));
//    b = qMax (0,
//              qMin (b, 255));
//    return QColor (r, g, b);
//}

//QRgb Graphic::matrixColorMul(QRgb colors[3][3], int matrix[3][3])
//{
//    int r = 0, g = 0, b = 0;
//    r = qRed(colors[0][0]) * matrix[0][0] + qRed(colors[0][1]) * matrix[0][1] + qRed(colors[0][2]) * matrix[0][2] +
//            qRed(colors[1][0]) * matrix[1][0] + qRed(colors[1][1] )* matrix[1][1] + qRed(colors[1][2]) * matrix[1][2] +
//            qRed(colors[2][0]) * matrix[2][0] + qRed(colors[2][1]) * matrix[2][1] + qRed(colors[2][2]) * matrix[2][2];
//    g = qGreen(colors[0][0]) * matrix[0][0] + qGreen(colors[0][1]) * matrix[0][1] + qGreen(colors[0][2]) * matrix[0][2] +
//            qGreen(colors[1][0]) * matrix[1][0] + qGreen(colors[1][1]) * matrix[1][1] + qGreen(colors[1][2]) * matrix[1][2] +
//            qGreen(colors[2][0]) * matrix[2][0] + qGreen(colors[2][1]) * matrix[2][1] + qGreen(colors[2][2]) * matrix[2][2];
//    b = qBlue(colors[0][0])* matrix[0][0] + qBlue(colors[0][1]) * matrix[0][1] + qBlue(colors[0][2]) * matrix[0][2] +
//            qBlue(colors[1][0]) * matrix[1][0] + qBlue(colors[1][1]) * matrix[1][1] + qBlue(colors[1][2]) * matrix[1][2] +
//            qBlue(colors[2][0]) * matrix[2][0] + qBlue(colors[2][1] )* matrix[2][1] + qBlue(colors[2][2]) * matrix[2][2];
//    r = qMax (0,
//              qMin (r, 255));
//    g = qMax (0,
//              qMin (g, 255));
//    b = qMax (0,
//              qMin (b, 255));
//    return qRgb (r, g, b);
//}

//unsigned char Graphic::matrixMul(unsigned char channel[3][3], int matrix[3][3])
//{
//    int c = 0;
//    c = channel[0][0] * matrix[0][0] + channel[0][1] * matrix[0][1] + channel[0][2] * matrix[0][2] +
//            channel[1][0] * matrix[1][0] + channel[1][1] * matrix[1][1] + channel[1][2] * matrix[1][2] +
//            channel[2][0] * matrix[2][0] + channel[2][1] * matrix[2][1] + channel[2][2] * matrix[2][2];
//    c = qMax (0,
//              qMin (c, 255));
//    return c;
//}

//QColor Graphic::colorNormir(QColor colorX, QColor colorY)
//{
//    double rx = colorX.red(), gx = colorX.green(), bx = colorX.blue();
//    double ry = colorY.red(), gy = colorY.green(), by = colorY.blue();
//    rx = sqrt(rx * rx + ry * ry);
//    gx = sqrt(gx * gx + gy * gy);
//    bx = sqrt(bx * bx + by * by);
//    int r = qMax (0,
//              qMin (static_cast <int> (rx), 255));
//    int g = qMax (0,
//              qMin (static_cast <int>(gx), 255));
//    int b = qMax (0,
//              qMin (static_cast <int>(bx), 255));
//    return QColor (r, g, b);
//}

//QRgb Graphic::colorNormir(QRgb colorX, QRgb colorY)
//{
//    double rx = qRed(colorX), gx = qGreen(colorX), bx = qBlue(colorX);
//    double ry = qRed(colorY), gy = qGreen(colorY), by = qBlue(colorY);
//    rx = sqrt(rx * rx + ry * ry);
//    gx = sqrt(gx * gx + gy * gy);
//    bx = sqrt(bx * bx + by * by);
//    int r = qMax (0,
//              qMin (static_cast <int> (rx), 255));
//    int g = qMax (0,
//              qMin (static_cast <int>(gx), 255));
//    int b = qMax (0,
//              qMin (static_cast <int>(bx), 255));
//    return qRgb (r, g, b);
//}

//unsigned char Graphic::componentNormir(unsigned char colorX, unsigned char colorY)
//{
//    return static_cast <unsigned char> (qMax (0,
//                 qMin (static_cast <int> (sqrt(colorX * colorX + colorY * colorY)), 255)));
//}



QImage *Graphic::getImage() const
{
    return image;
}

void Graphic::setImage(QImage *value)
{
//    if (image != nullptr)
//        delete image;

    if (imageRGB != nullptr)
        delete imageRGB;

    if (imageMono != nullptr)
        delete imageMono;


    image = new QImage (*value);

    imageRGB = new DoubleImageRGB (value);
    imageMono = new DoubleImageMono (value);
}

////установить значения интенсивности
//void Graphic::setGray()
//{
//    QRgb *imageBytes[height];
//    //построчно сканируем изображение
//    for (int i = 0; i < height; i++){
//        imageBytes[i] = (QRgb*)(image->scanLine(i));
//    }


//    imageDouble = new double [height * width];

//    for (int j = 0; j < height; j++)
//        for (int i = 0; i < width; i++){
//            imageDouble[j * width + i] = 0.213 * static_cast<double>(qRed(imageBytes[j][i]))  + 0.715 * static_cast<double>(qGreen(imageBytes[j][i])) + 0.072 * static_cast<double>(qBlue(imageBytes[j][i]));
//        }
//}

//void Graphic::setRGB()
//{
//    QRgb *imageBytes[height];
//    //построчно сканируем изображение
//    for (int i = 0; i < height; i++){
//        imageBytes[i] = (QRgb*)(image->scanLine(i));
//    }

//    r = new double [height * width];
//    g = new double [height * width];
//    b = new double [height * width];

//    for (int j = 0; j < height; j++)
//        for (int i = 0; i < width; i++){

//            r[j * width + i] = static_cast<double>(qRed(imageBytes[j][i])) / 255;
//            g[j * width + i] = static_cast<double>(qGreen(imageBytes[j][i])) / 255;
//            b[j * width + i] = static_cast<double>(qBlue(imageBytes[j][i])) / 255;
//        }
//}

////установить текущее изображение в виде матрицы double, чтобы с ним можно было производить манипуляции
//void Graphic::setImageDouble()
//{
//    QRgb *imageBytes[height];
//    //построчно сканируем изображение
//    for (int i = 0; i < height; i++){
//        imageBytes[i] = (QRgb*)(image->scanLine(i));
//    }
//    imageDouble = new double [height * width];
//    //Заполняем массив
//    for (int j = 0; j < height; ++j) //все строки
//        for (int i = 0; i < width; ++i) {
//            imageDouble[j * width + i] =  (unsigned int)(*imageBytes)[j * width + i] / 255;
//        }
//}

void Graphic::setImageFromDouble()
{
    imageMono->getImage(image);
}

void Graphic::setImageFromRGB()
{
    imageRGB->getImage(image);
}





void Graphic::setDerivateX()
{
    QList<QList<double> > core; //ядро свертки
    core.append(QList<double>({1, 0, -1}));
    core.append(QList<double>({2, 0, -2}));
    core.append(QList<double>({1, 0, -1}));

    imageMono->convolutionUniversal(core); //непосредственно вычисляем
}

void Graphic::setDerivateY()
{
    QList<QList<double> > core; //ядро свертки
    core.append(QList<double>({1, 2, 1}));
    core.append(QList<double>({0, 0, 0}));
    core.append(QList<double>({-1, -2, -1}));

    imageMono->convolutionUniversal(core); //непосредственно вычисляем
}

/*
 * вычислить величину градиента
 */
void Graphic::setGradient()
{
    ((DoubleImageMono*)imageMono)->setGradient();
}

/*
 * фильтр Гаусса
 */
void Graphic::gaussianFilter(double sigma)
{
    QList<QList<double> > core; //ядро свертки

    int sigmaInt = static_cast<int>(sigma) * 3;
    if (sigmaInt  % 2 == 0)
        ++sigmaInt;
    double coeff = 1 / (2 * M_PI * sigma * sigma);
    double delitel = 2 * sigma * sigma;

    for (int i = 1; i <= sigmaInt; i++){
        QList<double> str;
        for (int j = 1; j <= sigmaInt; j++) {
            str.append(coeff * exp(- (i * i + j * j) / delitel));
        }
        core.append(str);
    }

    imageMono->convolutionUniversal(core); //непосредственно вычисляем
}

void Graphic::gaussianFilterRGB(double sigma)
{
    QList<QList<double> > core; //ядро свертки

    double s = sigma * sigma * 2;

    int halfSize = static_cast<int>(sigma) * 3;
    if (halfSize  % 2 == 0)
        ++halfSize;

    for (int i = -halfSize; i <= halfSize; i++){
        QList<double> str;
        for (int j = -halfSize; j <= halfSize; j++) {
            str.append(exp(- (i * i + j * j) / s) / (M_PI * s));
        }
        core.append(str);
    }

    imageRGB->convolutionUniversal(core); //непосредственно вычисляем
}

void Graphic::gaussianFilterRGBSep(double sigma)
{
    QList<QList<double> > core; //ядро свертки

    double s = sigma * sigma * 2;

    int halfSize = static_cast<int>(sigma) * 3;
    if (halfSize  % 2 == 0)
        ++halfSize;

    QList<double> str;
    for (int i = -halfSize; i <= halfSize; i++){
        str.append(exp(- i * i / s) / (M_PI * s));
    }
    core.append(str);

    imageRGB->convolutionUniversal(core, true); //непосредственно вычисляем


    core.clear();
    for (int i = -halfSize; i <= halfSize; i++){
        QList<double> str;
        str.append(exp(- i * i / s) / (M_PI * s));
        core.append(str);
    }

    imageRGB->convolutionUniversal(core, true); //непосредственно вычисляем
}

void Graphic::getPyramids(int octaveCount, int levelCount, double sigma0)
{
    int k = pow(2.0, 1.0 / levelCount); //интервал между масштабами

    //удаляем старую пирамиду
    for (int var = 0; var < pyramide.count(); ++var) {
        delete pyramide[var];
    }
    pyramide.clear();

    for(int i = 0; i < octaveCount; i++){
        pyramide.append(new PyramideImage(imageRGB, i, 0));
        double sigma = sigma0;
        for (int j = 1; j < levelCount; j++){
            gaussianFilterRGB(sigma);
            sigma *= k;
            pyramide.append(new PyramideImage(imageRGB, i, j));
        }
        sigma = sigma0; //возвращаем сигма к прежнему значению

        if (i < octaveCount - 1)
            imageRGB->downSample(); //уменьшаем изображение
    }

    foreach (PyramideImage *currImage, pyramide) {
        QString path = QApplication::applicationDirPath() + "/Input/Pyramide/pyramide" + QString::number(currImage->getOctaveNum()) + "-"  + QString::number(currImage->getLayerNum()) + ".jpg";      //текущая директория

        currImage->getImage()->getImage()->save(path);
    }

}

void Graphic::setLIMIT(int value)
{
    LIMIT = value;
}

