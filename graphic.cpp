#include "graphic.h"



Graphic::Graphic(QWidget *parent) : QGraphicsView(parent)
{
    this->setAlignment(Qt::AlignCenter);        //выравнивание по центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    imageItem = nullptr;
    reserve = nullptr;
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



QColor Graphic::matrixColorMul(QColor colors[3][3], int matrix[3][3])
{
    int r = 0, g = 0, b = 0;
    r = colors[0][0].red() * matrix[0][0] + colors[0][1].red() * matrix[0][1] + colors[0][2].red() * matrix[0][2] +
            colors[1][0].red() * matrix[1][0] + colors[1][1].red() * matrix[1][1] + colors[1][2].red() * matrix[1][2] +
            colors[2][0].red() * matrix[2][0] + colors[2][1].red() * matrix[2][1] + colors[2][2].red() * matrix[2][2];
    g = colors[0][0].green() * matrix[0][0] + colors[0][1].green() * matrix[0][1] + colors[0][2].green() * matrix[0][2] +
            colors[1][0].green() * matrix[1][0] + colors[1][1].green() * matrix[1][1] + colors[1][2].green() * matrix[1][2] +
            colors[2][0].green() * matrix[2][0] + colors[2][1].green() * matrix[2][1] + colors[2][2].green() * matrix[2][2];
    b = colors[0][0].blue() * matrix[0][0] + colors[0][1].blue() * matrix[0][1] + colors[0][2].blue() * matrix[0][2] +
            colors[1][0].blue() * matrix[1][0] + colors[1][1].blue() * matrix[1][1] + colors[1][2].blue() * matrix[1][2] +
            colors[2][0].blue() * matrix[2][0] + colors[2][1].blue() * matrix[2][1] + colors[2][2].blue() * matrix[2][2];
    r = qMax (0,
              qMin (r, 255));
    g = qMax (0,
              qMin (g, 255));
    b = qMax (0,
              qMin (b, 255));
    return QColor (r, g, b);
}

QRgb Graphic::matrixColorMul(QRgb colors[3][3], int matrix[3][3])
{
    int r = 0, g = 0, b = 0;
    r = qRed(colors[0][0]) * matrix[0][0] + qRed(colors[0][1]) * matrix[0][1] + qRed(colors[0][2]) * matrix[0][2] +
            qRed(colors[1][0]) * matrix[1][0] + qRed(colors[1][1] )* matrix[1][1] + qRed(colors[1][2]) * matrix[1][2] +
            qRed(colors[2][0]) * matrix[2][0] + qRed(colors[2][1]) * matrix[2][1] + qRed(colors[2][2]) * matrix[2][2];
    g = qGreen(colors[0][0]) * matrix[0][0] + qGreen(colors[0][1]) * matrix[0][1] + qGreen(colors[0][2]) * matrix[0][2] +
            qGreen(colors[1][0]) * matrix[1][0] + qGreen(colors[1][1]) * matrix[1][1] + qGreen(colors[1][2]) * matrix[1][2] +
            qGreen(colors[2][0]) * matrix[2][0] + qGreen(colors[2][1]) * matrix[2][1] + qGreen(colors[2][2]) * matrix[2][2];
    b = qBlue(colors[0][0])* matrix[0][0] + qBlue(colors[0][1]) * matrix[0][1] + qBlue(colors[0][2]) * matrix[0][2] +
            qBlue(colors[1][0]) * matrix[1][0] + qBlue(colors[1][1]) * matrix[1][1] + qBlue(colors[1][2]) * matrix[1][2] +
            qBlue(colors[2][0]) * matrix[2][0] + qBlue(colors[2][1] )* matrix[2][1] + qBlue(colors[2][2]) * matrix[2][2];
    r = qMax (0,
              qMin (r, 255));
    g = qMax (0,
              qMin (g, 255));
    b = qMax (0,
              qMin (b, 255));
    return qRgb (r, g, b);
}

unsigned char Graphic::matrixMul(unsigned char channel[3][3], int matrix[3][3])
{
    int c = 0;
    c = channel[0][0] * matrix[0][0] + channel[0][1] * matrix[0][1] + channel[0][2] * matrix[0][2] +
            channel[1][0] * matrix[1][0] + channel[1][1] * matrix[1][1] + channel[1][2] * matrix[1][2] +
            channel[2][0] * matrix[2][0] + channel[2][1] * matrix[2][1] + channel[2][2] * matrix[2][2];
    c = qMax (0,
              qMin (c, 255));
    return c;
}

QColor Graphic::colorNormir(QColor colorX, QColor colorY)
{
    double rx = colorX.red(), gx = colorX.green(), bx = colorX.blue();
    double ry = colorY.red(), gy = colorY.green(), by = colorY.blue();
    rx = sqrt(rx * rx + ry * ry);
    gx = sqrt(gx * gx + gy * gy);
    bx = sqrt(bx * bx + by * by);
    int r = qMax (0,
              qMin (static_cast <int> (rx), 255));
    int g = qMax (0,
              qMin (static_cast <int>(gx), 255));
    int b = qMax (0,
              qMin (static_cast <int>(bx), 255));
    return QColor (r, g, b);
}

QRgb Graphic::colorNormir(QRgb colorX, QRgb colorY)
{
    double rx = qRed(colorX), gx = qGreen(colorX), bx = qBlue(colorX);
    double ry = qRed(colorY), gy = qGreen(colorY), by = qBlue(colorY);
    rx = sqrt(rx * rx + ry * ry);
    gx = sqrt(gx * gx + gy * gy);
    bx = sqrt(bx * bx + by * by);
    int r = qMax (0,
              qMin (static_cast <int> (rx), 255));
    int g = qMax (0,
              qMin (static_cast <int>(gx), 255));
    int b = qMax (0,
              qMin (static_cast <int>(bx), 255));
    return qRgb (r, g, b);
}

unsigned char Graphic::componentNormir(unsigned char colorX, unsigned char colorY)
{
    return static_cast <unsigned char> (qMax (0,
                 qMin (static_cast <int> (sqrt(colorX * colorX + colorY * colorY)), 255)));
}




QImage *Graphic::getImage() const
{
    return image;
}

void Graphic::setImage(QImage *value)
{
    image = new QImage (*value);
    width = image->width();
    height = image->height();
}

//установить значения интенсивности
void Graphic::setGray()
{
    QRgb *imageBytes[height];
    //построчно сканируем изображение
    for (int i = 0; i < height; i++){
        imageBytes[i] = (QRgb*)(image->scanLine(i));
    }


    imageDouble = new double [height * width];

    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++){
            imageDouble[j * width + i] = 0.213 * static_cast<double>(qRed(imageBytes[j][i]))  + 0.715 * static_cast<double>(qGreen(imageBytes[j][i])) + 0.072 * static_cast<double>(qBlue(imageBytes[j][i]));
        }
}

//установить текущее изображение в виде матрицы double, чтобы с ним можно было производить манипуляции
void Graphic::setImageDouble()
{
    QRgb *imageBytes[height];
    //построчно сканируем изображение
    for (int i = 0; i < height; i++){
        imageBytes[i] = (QRgb*)(image->scanLine(i));
    }
    imageDouble = new double [height * width];
    //Заполняем массив
    for (int j = 0; j < height; ++j) //все строки
        for (int i = 0; i < width; ++i) {
            imageDouble[j * width + i] =  (unsigned int)(*imageBytes)[j * width + i];
        }
}

void Graphic::setImageFromDouble()
{
    QRgb *imageBytes[height];
    //построчно сканируем изображение
    for (int i = 0; i < height; i++){
        imageBytes[i] = (QRgb*)(image->scanLine(i));
    }

    //устанавливаем значения для изображения
    for (int j = 0; j < height; ++j) //все строки
        for (int i = 0; i < width; ++i) {
            int colorVal = static_cast<int>(fmax(fmin (imageDouble[j * width + i], 255), 0));
            imageBytes[j][i] = qRgb(colorVal, colorVal, colorVal);
        }
}



/*
 * универсальная свертка, применяется к *image
 */
void Graphic::convolutionUniversal(double *image, int w, int h, QList<QList<double> > core)
{
//списки в ядре располагаются по горизонтали, поэтому размеры берутся так а не иначе
    int coreW = core[0].count() / 2;
    int coreH = core.count() / 2;

    int widthWorking = w + coreW * 2;    //ширина и высота расширенного, рабочего изображения
    int heightWorking = h + coreH * 2;

    //расширяем изображение на размер ядра
    double *imageWorking = new double [widthWorking * heightWorking]; //расширенное рабочее изображение

    //Заполняем рабочее изображение
    for (int j = 0; j < heightWorking; ++j) //все строки
        for (int i = 0; i < widthWorking; ++i) {
            //Здесь мы просто точки, лежащие за границей, приравниваем граничным =)
            imageWorking[j * widthWorking + i] = image[(j - coreH < 0 ? 0 : (j + coreH > height - 1 ? height - 1 : j)) * width + (i - coreW < 0 ? 0 : (i + coreW > width - 1 ? width - 1 : i))];
        }

    int xSize = core[0].count();
    int ySize = core.count();

    //применяем свертку ко всем точкам
    for (int j = 0; j < height; ++j) //все строки
        for (int i = 0; i < width; ++i) {
            double sum = 0; //результат свертки для одной точки

            for (int u = 0; u < ySize; u++)//для каждого ряда в ядре
                for (int v = 0; v < xSize; v++)  //для каждого значения в ряду
                    sum += imageWorking[(j + v) * widthWorking + (i + u)] * core[v][u]; //здесь учитываем что coreW == (core[0].count() - 1) / 2, coreH аналогично

            image[j * width + i] = sum;
        }
}

void Graphic::setDerivateX()
{
    QList<QList<double> > core; //ядро свертки
    core.append(QList<double>({-1, 0, 1}));
    core.append(QList<double>({-2, 0, 2}));
    core.append(QList<double>({-1, 0, 1}));

    convolutionUniversal(imageDouble, width, height, core); //непосредственно вычисляем
}

void Graphic::setDerivateY()
{
    QList<QList<double> > core; //ядро свертки
    core.append(QList<double>({-1, -2, -1}));
    core.append(QList<double>({0, 0, 0}));
    core.append(QList<double>({1, 2, 1}));

    convolutionUniversal(imageDouble, width, height, core); //непосредственно вычисляем
}

/*
 * вычислить величину градиента
 */
void Graphic::setGradient()
{
    setDerivateX(); //получаем производную по X
    double* derivateX = imageDouble;
    setGray();
    setDerivateY(); //получаем производную по Y
    //считаем величину градиента
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            imageDouble[j * width + i] = sqrt(imageDouble[j * width + i] * imageDouble[j * width + i] +
                    derivateX[j * width + i] * derivateX[j * width + i]);
        }
    }
}

void Graphic::setLIMIT(int value)
{
    LIMIT = value;
}


