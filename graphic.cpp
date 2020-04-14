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

void Graphic::getPyramide(int octaveCount, int levelCount, double sigmaA, double sigma0)
{
    double k = pow(2.0, 1.0 / (levelCount - 1)); //интервал между масштабами
    double sigmaB = sqrt(sigma0 * sigma0 - sigmaA * sigmaA);    //с каким сигма нужно сгладить, чтобы получить с требуемым sigma0
    gaussianFilterRGBSep(sigmaB);   //досглаживаем изображение

    double sigma[levelCount - 1];   //массив с sigma, которые будут применяться к слоям
    double sigmaOld = sigma0;
    for (int i = 0; i < levelCount - 1; i++) {
        double sigmaNew = sigmaOld * k;
        sigma[i] = sqrt(sigmaNew * sigmaNew - sigmaOld * sigmaOld);
        sigmaOld = sigmaNew;
    }

    //удаляем старую пирамиду
    for (int var = 0; var < pyramide.count(); ++var) {
        delete pyramide[var];
    }
    pyramide.clear();

    double sigmaEff = sigma0;
    QList <PyramideImage*> *oneOctave;  //одна октава
    PyramideImage *currentLayer;



    for(int i = 0; i < octaveCount; i++){
        oneOctave = new QList <PyramideImage*>();   //создаем новую октаву
        double sigmaLocal = sigma0;

        currentLayer = new PyramideImage(imageRGB, i, 0);   //создаем новый слой и добавляем в пирамиду
        currentLayer->setSigmaLocal(sigmaLocal);
        currentLayer->setSigmaEffective(sigmaEff);
        oneOctave->append(currentLayer);

        for (int j = 1; j < levelCount; j++){
            gaussianFilterRGBSep(sigma[j - 1]);
            sigmaLocal *= k;
            sigmaEff *= k;
            currentLayer = new PyramideImage(imageRGB, i, j);   //создаем новый слой и добавляем в пирамиду
            currentLayer->setSigmaLocal(sigmaLocal);
            currentLayer->setSigmaEffective(sigmaEff);
            oneOctave->append(currentLayer);
        }
        pyramide.append(new Octave(oneOctave, i));

        if (i < octaveCount - 1)
            imageRGB->downSample(); //уменьшаем изображение
    }

    //сохраняем
    foreach (Octave *octave, pyramide)
        foreach (PyramideImage *currImage, *octave->getLayers()) {
            QString path = QApplication::applicationDirPath() + "/Input/Pyramide/pyramide" + QString::number(currImage->getOctaveNum() + 1) + "-"  + QString::number(currImage->getLayerNum() + 1) + ".jpg";      //текущая директория

            currImage->getImage()->getImage()->save(path);
        }

}

//функция L(x, y, sigma)
double Graphic::getL(QList<Octave *> pyramide, int y, int x, double sigma, int colorNum)
{
    //компаратор для сравнения двух слоев, у какого sigmaEff ближе к sigma
    auto comp = [sigma](const PyramideImage* _first_layer, const PyramideImage* _second_layer) {
        return fabs(_first_layer->getSigmaEffective() - sigma) < fabs(_second_layer->getSigmaEffective() - sigma);
    };

    PyramideImage* target_layer = pyramide.front()->getLayers()->first();
    int octaveLevel = pyramide.front()->getOctave();
    for (Octave * octave : pyramide) {
        PyramideImage* layer = std::min_element(octave->getLayers()->begin(), octave->getLayers()->end(), comp).i->t(); //выбираем наиболее близкий слой из октавы
        if (comp(layer, target_layer)) {
            target_layer = layer;
            octaveLevel = octave->getOctave();
        }
    }

    int w = target_layer->getImage()->getWidth();   //ширина изображения
    y = static_cast<int>(y / pow(2.0, octaveLevel)); //учитываем, что на следующих октавах изображения меньше по размеру
    x = static_cast<int>(x / pow(2.0, octaveLevel));

    return ((DoubleImageRGB*)target_layer->getImage())->getColorMatrix(colorNum)[y * w + x];
}


void Graphic::setMoravek(int winSize, int pointCount)
{
    int w = imageMono->getWidth();
    int h = imageMono->getHeight();
    QList <InterestingPoint> interestingPoints;
    //double *s = new double[w * h]; //массив контрастностей

    //вычисляем во всех точках
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            double sLocal = std::numeric_limits<double>::max(); //сначала берем максимальное число
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx != 0 && dy != 0) {
                        double c = getC(winSize, i, j, dx, dy); //значение коэфф. при заданном векторе сдвига
                        sLocal = std::min(sLocal, c);
                    }
                }
            }
            interestingPoints.append(InterestingPoint(i, j, sLocal));
        }
    }

    std::sort(interestingPoints.begin(), interestingPoints.end(), InterestingPoint::operatorMore);  //сортируем в порядке убывания

    while (interestingPoints.length() > pointCount)
        interestingPoints.removeLast(); //оставляем самые-самые точки

    foreach (InterestingPoint point, interestingPoints) {
        imageRGB->setPixel(point.getX(), point.getY(), 1, 0, 0);  //красим точки
    }
}

void Graphic::setLIMIT(int value)
{
    LIMIT = value;
}

double Graphic::getC(int winSize, int x, int y, int dx, int dy)
{
    double sum = 0;
    auto winSizeHalf = winSize / 2;

    for (int u = -winSizeHalf; u <= winSizeHalf; u++) {
        for (int v = -winSizeHalf; v <= winSizeHalf; v++) {
            double tmp =  ((DoubleImageMono*)imageMono)->getPixel(x + u, y + v) - ((DoubleImageMono*)imageMono)->getPixel(x + u + dx, y + v + dy);
            sum += tmp * tmp;
        }
    }

    return sum;
}

