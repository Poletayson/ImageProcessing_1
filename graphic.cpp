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
    imageMono->setDerivateX();// convolutionUniversal(core); //непосредственно вычисляем
}

void Graphic::setDerivateY()
{
    imageMono->setDerivateY();
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

void Graphic::gaussianFilterMonoSep(double sigma)
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

    imageMono->convolutionUniversal(core, true); //непосредственно вычисляем


    core.clear();
    for (int i = -halfSize; i <= halfSize; i++){
        QList<double> str;
        str.append(exp(- i * i / s) / (M_PI * s));
        core.append(str);
    }

    imageMono->convolutionUniversal(core, true); //непосредственно вычисляем
}

void Graphic::getPyramide(int octaveCount, int levelCount, double sigmaA, double sigma0)
{
    long full_time = clock();

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

    qDebug() << "\n\nFULL TIME : " << (clock() - full_time) / 1000.0 << "\n";
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

//применить оператор Моравека
QList <InterestingPoint> Graphic::setMoravek(int winSize, int pointCount, bool isCount)
{
    int w = imageMono->getWidth();
    int h = imageMono->getHeight();

    DoubleImageMono imageS (new QImage(w, h, QImage::Format_RGB32));    //здесь будем хранить значения оператора

    gaussianFilterMonoSep(1.3);

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
            imageS.setPixel(i, j, sLocal);
            //interestingPoints.append(InterestingPoint(i, j, sLocal));
        }
    }

//    imageS.save("MoavekOtklik.jpg");
    QList <InterestingPoint> interestingPoints = getLocalMaximums(imageS, 3);

    interestingPoints = filterPoints(interestingPoints, pointCount);

//    std::sort(interestingPoints.begin(), interestingPoints.end(), InterestingPoint::operatorMore);  //сортируем в порядке убывания
//    while (interestingPoints.length() > pointCount)
//        interestingPoints.removeLast(); //оставляем самые-самые точки


//    foreach (InterestingPoint point, interestingPoints) {
//        imageRGB->setPixel(point.getX() - 1, point.getY(), 1, 1, 1);  //красим точки
//        imageRGB->setPixel(point.getX() + 1, point.getY(), 1, 1, 1);  //красим точки
//        imageRGB->setPixel(point.getX(), point.getY(), 1, 1, 1);  //красим точки
//        imageRGB->setPixel(point.getX(), point.getY() - 1, 1, 1, 1);  //красим точки
//        imageRGB->setPixel(point.getX(), point.getY() + 1, 1, 1, 1);  //красим точки
//    }

    return interestingPoints;
}

//применить оператор Харриса
QList <InterestingPoint> Graphic::setHarris(int winSize, int pointCount, bool isCount, double k)
{
    gaussianFilterMonoSep(1.3); //немного сглаживаем
    //находим производные
    DoubleImageMono dx = DoubleImageMono(imageMono->getImage());
    DoubleImageMono dy = DoubleImageMono(imageMono->getImage());
    dx.setDerivateX();
    dy.setDerivateY();


    int w = imageMono->getWidth();
    int h = imageMono->getHeight();
    double *a = new double [w * h];
    double *b = new double [w * h];
    double *c = new double [w * h];
    int halfSize = winSize / 2;


    //находим веса для окна - ядро Гаусса
    double sigma = static_cast<double>(winSize) / 6;
    double *gaussKernel = new double[winSize * winSize];

    double coeff = 1 / (2 * M_PI * sigma * sigma);
    double delitel = 2 * sigma * sigma;

    for (int u = -halfSize; u <= halfSize; u++)
        for (int v = -halfSize; v <= halfSize; v++){
            gaussKernel[(u + halfSize) * halfSize + (v  + halfSize)] = coeff * exp(- (u * u + v * v) / delitel);
//            qDebug() << gaussKernel[(u + halfSize) * halfSize + (v  + halfSize)];
        }
//qDebug() << "\n\n";

    //Вычисляем A, B, C для всех точек
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            double sumA = 0, sumB = 0, sumC = 0;
            for (int u = -halfSize; u <= halfSize; u++) {
                for (int v = -halfSize; v <= halfSize; v++) {
                    double i_x = dx.getPixel(i + u, j + v);
                    double i_y = dy.getPixel(i + u, j + v);
                    sumA += i_x * i_x * gaussKernel[u * halfSize + v];
                    sumB += i_x * i_y * gaussKernel[u * halfSize + v];
                    sumC += i_y * i_y * gaussKernel[u * halfSize + v];
                }
            }
            a[j * w + i] = sumA;
            b[j * w + i] = sumB;
            c[j * w + i] = sumC;
//            qDebug() << sumA << " " << sumB << " " << sumC;
        }
    }


    DoubleImageMono imageS (new QImage(w, h, QImage::Format_RGB32));    //здесь будем хранить значения оператора

//    for (int j = 0; j < h; j++) {
//        for (int i = 0; i < w; i++) {
//            double det = a[j * w + i] * c[j * w + i] - b[j * w + i] * b[j * w + i];
//            double trace = a[j * w + i] + c[j * w + i];
//            double cHarris = det / trace;
//            imageS.setPixel(i, j, abs(cHarris));
//            qDebug() << cHarris;
//        }
//    }

    //вариант с собств. числами
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            double sc = a[j * w + i] + c[j * w + i];
            double d = a[j * w + i] * c[j * w + i] - b[j * w + i] * b[j * w + i];
            double det = sc * sc - 4 * d;
            double L1 = (sc + sqrt(det)) / 2;
            double L2 = (sc - sqrt(det)) / 2;
            double cHarris = std::min (L1, L2);
            imageS.setPixel(i, j, cHarris);
            //qDebug() << L1 << " " << L2;
        }
    }


    QList <InterestingPoint> interestingPoints = getLocalMaximums(imageS, 5, true);


//    imageS.save("HarrisOtklik.jpg");

    interestingPoints = filterPoints(interestingPoints, pointCount);

//    std::sort(interestingPoints.begin(), interestingPoints.end(), InterestingPoint::operatorMore);  //сортируем в порядке возрастания
//    while (interestingPoints.length() > pointCount)
//        interestingPoints.removeLast(); //оставляем самые-самые точки


//    foreach (InterestingPoint point, interestingPoints) {
//        imageRGB->setPixel(point.getX() - 1, point.getY(), 1, 1, 1);  //красим точки
//        imageRGB->setPixel(point.getX() + 1, point.getY(), 1, 1, 1);  //красим точки
//        imageRGB->setPixel(point.getX(), point.getY(), 1, 1, 1);  //красим точки
//        imageRGB->setPixel(point.getX(), point.getY() - 1, 1, 1, 1);  //красим точки
//        imageRGB->setPixel(point.getX(), point.getY() + 1, 1, 1, 1);  //красим точки
//    }
    delete[] a;
    delete[] b;
    delete[] c;
    delete[] gaussKernel;

    return interestingPoints;
}

QList<InterestingPoint> Graphic::getDescriptors(int pointCount, int basketCount, int histCount, int gridSize)
{
    int w = imageMono->getWidth();
    int h = imageMono->getHeight();

    QList <InterestingPoint> interestingPoints = setHarris(3, pointCount);  //получаем интересные точки

    DescriptorConstructor descriptorConstructor (imageMono);
    //interestingPoints = descriptorConstructor.orientPoints(interestingPoints);  //определяем углы точек

    for (int i = 0, endI = interestingPoints.count(); i < endI; i ++){
        interestingPoints[i].setDescroptor(descriptorConstructor.createDescriptor(interestingPoints[i]));   //для каждой точки устанавливаем дескриптор
    }

    return interestingPoints;
}

void Graphic::setLIMIT(int value)
{
    LIMIT = value;
}

DoubleImageRGB *Graphic::getImageRGB() const
{
    return imageRGB;
}

//получить ошибку при сдвиге окна
double Graphic::getC(int winSize, int x, int y, int dx, int dy)
{
    double sum = 0;
    auto winSizeHalf = winSize / 2;

    for (int u = -winSizeHalf; u <= winSizeHalf; u++) {
        for (int v = -winSizeHalf; v <= winSizeHalf; v++) {
            double tmp =  imageMono->getPixel(x + u, y + v) - imageMono->getPixel(x + u + dx, y + v + dy);
            sum += tmp * tmp;
        }
    }

    return sum;
}

//получить локальные максимумы
QList<InterestingPoint> Graphic::getLocalMaximums(DoubleImageMono pointsImage, int winSize, bool isHarris)
{
    QList <InterestingPoint> points;

    int w = imageMono->getWidth();
    int h = imageMono->getHeight();
    int halfSize = winSize / 2; //полуразмер окна

    //находим мин и макс для порога
    double min = std::numeric_limits <double>::max(), max = std::numeric_limits <double>::min();
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            if (max < pointsImage.getPixel(i, j))
                max = pointsImage.getPixel(i, j);
            if (min > pointsImage.getPixel(i, j))
                min = pointsImage.getPixel(i, j);
        }
    }

    //задаем порог
    double threshold = min + (max - min) * 0.005;
    if (isHarris)
        threshold = min + (max - min) * 0.004;
    qDebug() << min << " " << max << " " << threshold;


    //добавляем точки в список, только если они сильнейшие в своей окрестности
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            bool is_correct = true;
            double sLocal = pointsImage.getPixel(i, j);
            for (int px = -halfSize; px <= halfSize && is_correct; px++) {
                for (int py = -halfSize; py <= halfSize && is_correct; py++) {
                    if (px != 0 || py != 0) {
                        is_correct = sLocal > pointsImage.getPixel(i + px, j + py);
                    }
                }
            }
            if (is_correct && sLocal > threshold) {
                points.append(InterestingPoint(i, j, sLocal));;
            }
        }
    }

    return points;
}

//отфильтровать точки до заданного количества (ANMS)
QList<InterestingPoint> Graphic::filterPoints(QList<InterestingPoint> pointsIn, int count)
{
    QList<InterestingPoint> points (pointsIn);

    int r = 1;

    //пока точек слишком много и радиус в пределах допустимого
    while (points.size() > count && r < imageMono->getWidth() / 2 && r < imageMono->getHeight() / 2) {
        points.erase(std::remove_if(points.begin(), points.end(),
            [&](const InterestingPoint& curPoint) {   //лямбда-функция, захватываем все локальные переменные по ссылке
                for (const InterestingPoint& point : points) {
                    double dst = InterestingPoint::getDistance(point, curPoint);  //расстояние
                    //если точки достаточно близко и вторая точка сильнее
                    if (dst < r && curPoint.getC() < point.getC()) {
                        return true;
                    }
                }
                return false;
            }), points.end());
        r++;
    }

    return points;
}

