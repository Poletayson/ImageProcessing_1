#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfile.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    path = QApplication::applicationDirPath();  //QDir::currentPath();      //текущая директория
    if (!QDir(path + "/Input").exists())
        QDir(path).mkdir("Input");
    path = path + "/Input";

    myGraphic = new Graphic ();
    myGraphic2 = new Graphic ();

    ui->horizontalLayout->addWidget(myGraphic);
    ui->horizontalLayout->addWidget(myGraphic2);

    random = new QRandomGenerator ();

   connect(ui->open, SIGNAL(triggered(bool)), this, SLOT(getFile()));
   connect(ui->save, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
   //connect(ui->ButtonRepair, SIGNAL(clicked()), this, SLOT(Repair ()));
   connect(ui->buttonDerivateX, SIGNAL(clicked()), this, SLOT(setDerivateX ()));
   connect(ui->buttonDerivateY, SIGNAL(clicked()), this, SLOT(setDerivateY ()));
   connect(ui->buttonGradient, SIGNAL(clicked()), this, SLOT(setGradient ()));
   connect(ui->ButtonGauss, SIGNAL(clicked()), this, SLOT(setGauss ()));
   connect(ui->buttonPyramides, SIGNAL(clicked()), this, SLOT(getPyramide()));
   connect(ui->buttonMoravek, SIGNAL(clicked()), this, SLOT(getMoravec()));
   connect(ui->buttonHarris, SIGNAL(clicked()), this, SLOT(getHarris()));
   connect(ui->buttonDescriptors, SIGNAL(clicked()), this, SLOT(getDescriptors()));

   myGraphic2->setLIMIT(ui->horizontalSlider->value());

   ui->ButtonRepair->hide();

   image = new QImage ();
}



MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::setInterfaceDisabled(bool f)
{
    ui->buttonDerivateX->setDisabled(f);
    ui->buttonDerivateY->setDisabled(f);
    ui->buttonGradient->setDisabled(f);
    ui->ButtonGauss->setDisabled(f);
    ui->buttonPyramides->setDisabled(f);
}



void MainWindow::getFile()             //выбираем файл
{
    QString fileName = QFileDialog::getOpenFileName(Q_NULLPTR, "Выберите входной файл", path);
    //получили файл
    if (! fileName.isEmpty()){
        myGraphic->GetFileImage(fileName);      //получаем изображение
        setStart ();
    }
}

void MainWindow::saveFile()
{
    #include <QDir>
    QString path = QApplication::applicationDirPath();  //QDir::currentPath();      //текущая директория
    if (QDir(path + "/Input").exists())
         path = path + "/Input";
    else
        QDir(path).mkdir("Input");
    QString fileName = QFileDialog::getSaveFileName(Q_NULLPTR, "Сохранить", path);
    //получили имя
    myGraphic2->getImage()->save(fileName);
}



void MainWindow::setStart ()
{
    if (myGraphic2->imageItem != nullptr)
        delete myGraphic2->imageItem;
    myGraphic2->imageItem = myGraphic2->myScene->addPixmap(myGraphic->imageItem->pixmap());
    myGraphic2->myScene->setSceneRect(0, 0, myGraphic2->imageItem->pixmap().width(), myGraphic2->imageItem->pixmap().height());
    if (myGraphic2->reserve != nullptr)
        delete myGraphic2->reserve;
    myGraphic2->reserve = new QGraphicsPixmapItem (myGraphic2->imageItem->pixmap());
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    myGraphic2->setLIMIT(value);
}


void MainWindow::setDerivateX()
{
    delete image;
    delete myGraphic2->imageItem;

    myGraphic2->setImage(myGraphic->getImage());

    myGraphic2->setDerivateX(); //вычисляем частную производную по X

    myGraphic2->setImageFromDouble();   //переводим матрицу обратно в Image
    image = myGraphic2->getImage();

    myGraphic2->imageItem = myGraphic2->myScene->addPixmap(QPixmap::fromImage(*image));
}

void MainWindow::setDerivateY()
{
    delete image;
    delete myGraphic2->imageItem;

    myGraphic2->setImage(myGraphic->getImage());

    myGraphic2->setDerivateY(); //вычисляем частную производную по Y

    myGraphic2->setImageFromDouble();   //переводим матрицу обратно в Image
    image = myGraphic2->getImage();

    myGraphic2->imageItem = myGraphic2->myScene->addPixmap(QPixmap::fromImage(*image));
}

void MainWindow::setGradient()
{
    setInterfaceDisabled(true);

    delete image;
    delete myGraphic2->imageItem;
    myGraphic2->setImage(myGraphic->getImage());

    myGraphic2->setGradient(); //вычисляем значения градиента

    myGraphic2->setImageFromDouble();   //переводим матрицу обратно в Image
    image = myGraphic2->getImage();

    myGraphic2->imageItem = myGraphic2->myScene->addPixmap(QPixmap::fromImage(*image)); //устанавливаем новую картинку
    setInterfaceDisabled(false);
}

void MainWindow::setGauss()
{
    setInterfaceDisabled(true);

    delete image;
    delete myGraphic2->imageItem;

    myGraphic2->setImage(myGraphic->getImage());

    myGraphic2->gaussianFilterRGBSep(static_cast<double>(ui->horizontalSlider->value()) / 10); //применяем фильтр Гаусса

    myGraphic2->setImageFromRGB();   //переводим матрицу обратно в Image
    image = myGraphic2->getImage();

    myGraphic2->imageItem = myGraphic2->myScene->addPixmap(QPixmap::fromImage(*image));
    setInterfaceDisabled(false);
}

void MainWindow::getPyramide()
{
    setInterfaceDisabled(true);

    delete image;

    myGraphic2->myScene->removeItem(myGraphic2->imageItem);
    delete myGraphic2->imageItem;

    myGraphic2->setImage(myGraphic->getImage());

    myGraphic2->getPyramide(ui->spinBoxOctavaCount->value(), ui->spinBoxLevelCount->value(), ui->horizontalSliderSigma2->value() / 10, ui->horizontalSlider->value() / 10); //строим пирамиду

    myGraphic2->setImageFromRGB();   //переводим матрицу обратно в Image
    image = myGraphic2->getImage();


    myGraphic2->imageItem = myGraphic2->myScene->addPixmap(QPixmap::fromImage(*image));

    setInterfaceDisabled(false);
}

void MainWindow::getMoravec()
{
    setInterfaceDisabled(true);

    delete image;
    delete myGraphic2->imageItem;

    myGraphic2->setImage(myGraphic->getImage());

    QList<InterestingPoint> interestingPoints = myGraphic2->setMoravek(5, ui->horizontalSliderPointsCount->value()); //оператор Моравека

    for(int i = 0; i < interestingPoints.size(); i++){

            myGraphic2->getImageRGB()->setPixel(interestingPoints.at(i).getX() - 1, interestingPoints.at(i).getY(), 1, 1, 1);  //красим точки
            myGraphic2->getImageRGB()->setPixel(interestingPoints.at(i).getX() + 1, interestingPoints.at(i).getY(), 1, 1, 1);  //красим точки
            myGraphic2->getImageRGB()->setPixel(interestingPoints.at(i).getX(), interestingPoints.at(i).getY(), 1, 1, 1);  //красим точки
            myGraphic2->getImageRGB()->setPixel(interestingPoints.at(i).getX(), interestingPoints.at(i).getY() - 1, 1, 1, 1);  //красим точки
            myGraphic2->getImageRGB()->setPixel(interestingPoints.at(i).getX(), interestingPoints.at(i).getY() + 1, 1, 1, 1);  //красим точки
    }

    myGraphic2->setImageFromRGB();   //переводим матрицу обратно в Image
    image = myGraphic2->getImage();

    myGraphic2->imageItem = myGraphic2->myScene->addPixmap(QPixmap::fromImage(*image));

    setInterfaceDisabled(false);
}

void MainWindow::getHarris()
{
    setInterfaceDisabled(true);

    delete image;
    delete myGraphic2->imageItem;

    myGraphic2->setImage(myGraphic->getImage());

    QList<InterestingPoint> interestingPoints = myGraphic2->setHarris(3, ui->horizontalSliderPointsCount->value()); //оператор Харриса

        foreach (InterestingPoint point, interestingPoints) {
            myGraphic2->getImageRGB()->setPixel(point.getX() - 1, point.getY(), 1, 1, 1);  //красим точки
            myGraphic2->getImageRGB()->setPixel(point.getX() + 1, point.getY(), 1, 1, 1);  //красим точки
            myGraphic2->getImageRGB()->setPixel(point.getX(), point.getY(), 1, 1, 1);  //красим точки
            myGraphic2->getImageRGB()->setPixel(point.getX(), point.getY() - 1, 1, 1, 1);  //красим точки
            myGraphic2->getImageRGB()->setPixel(point.getX(), point.getY() + 1, 1, 1, 1);  //красим точки
        }

    myGraphic2->setImageFromRGB();   //переводим матрицу обратно в Image
    image = myGraphic2->getImage();

    myGraphic2->imageItem = myGraphic2->myScene->addPixmap(QPixmap::fromImage(*image));

    setInterfaceDisabled(false);
}

void MainWindow::getDescriptors()
{
    setInterfaceDisabled(true);

    delete image;
    delete myGraphic2->imageItem;

    myGraphic2->setImage(myGraphic->getImage());
    QList<InterestingPoint> points1 = myGraphic2->getDescriptors(ui->horizontalSliderPointsCount->value()); //получить дескрипторы
//    foreach (InterestingPoint p, points1) {
//        qDebug()<<p.getDescroptor().toString();
//    }
    qDebug()<<"Desc1 getted";

    Graphic *gaphicTransformed = new Graphic ();
    gaphicTransformed->setImage(new QImage (path + "/Lena2.jpg"));
//    qDebug()<<"Size " << gaphicTransformed->getImage()->width() << " " << gaphicTransformed->getImage()->height();
    qDebug()<<path + "/transformed.jpg";
    QList<InterestingPoint> points2 = gaphicTransformed->getDescriptors(ui->horizontalSliderPointsCount->value()); //получить дескрипторы
//    foreach (InterestingPoint p, points2) {
//        qDebug()<<p.getDescroptor().toString();
//    }
    qDebug()<<"Desc2 getted";
    //получили дескрипторы для двух картинок

    double *distances = new double[points1.size() * points2.size()];

    double minValue = std::numeric_limits<double>::max();
    double maxValue = std::numeric_limits<double>::min();
    double middleValue = 0;

    //Мин Макс и среднее
    for(int i = 0; i < points1.size(); i++){
        for(int j = 0; j < points2.size(); j++){
            double dist = Utils::getDescriptorDistance(points1.at(i).getDescroptor(), points2.at(j).getDescroptor());
            distances[i * points2.size() + j] = dist;
            middleValue += dist;
            if(dist < minValue){
                minValue = dist;
            }
            if(dist > maxValue){
                maxValue = dist;
            }
        }
    }
    middleValue /= points1.size() * points2.size();
    qDebug()<<"MinDist: " << minValue <<" MaxDist: " << maxValue << "middle: " << middleValue;


    //Поиск соответствий
    for(int i = 0; i < points1.size(); i++){
        double firstMinValue = std::numeric_limits<double>::max();
        int firstMinIndex = 0;
        double secondMinValue = std::numeric_limits<double>::max();
        int secondMinIndex = 0;

        for(int j = 0; j < points2.size(); j++){
            double dist = distances[i * points2.size() + j];//Utils::getDescriptorDistance(points1.at(i).getDescroptor(), points2.at(j).getDescroptor());
            if(dist < firstMinValue){
                secondMinValue = firstMinValue;
                secondMinIndex = firstMinIndex;

                firstMinValue = dist;
                firstMinIndex = j;
            } else {
                if(dist < secondMinValue){
                    secondMinValue = dist;
                    secondMinIndex = j;
                }
            }
        }
         //qDebug()<<"firstMinValue: " << firstMinValue <<" secondMinValue: " << secondMinValue;
        //берем точку если у нее NNDR < 0.8 (борьба с многозначностью)
        if(firstMinValue / secondMinValue < 0.8 && firstMinValue < middleValue * 0.8){

            double r = static_cast<double>(rand() % 255)  / 255;
            double g = static_cast<double>(rand() % 255) / 255;
            double b = static_cast<double>(rand() % 255) / 255;


            myGraphic2->getImageRGB()->setPixel(points1.at(i).getX() - 1, points1.at(i).getY(), r, g, b);  //красим точки
            myGraphic2->getImageRGB()->setPixel(points1.at(i).getX() + 1, points1.at(i).getY(), r, g, b);  //красим точки
            myGraphic2->getImageRGB()->setPixel(points1.at(i).getX(), points1.at(i).getY(), r, g, b);  //красим точки
            myGraphic2->getImageRGB()->setPixel(points1.at(i).getX(), points1.at(i).getY() - 1, r, g, b);  //красим точки
            myGraphic2->getImageRGB()->setPixel(points1.at(i).getX(), points1.at(i).getY() + 1, r, g, b);  //красим точки

            gaphicTransformed->getImageRGB()->setPixel(points2.at(firstMinIndex).getX() - 1, points2.at(firstMinIndex).getY(), r, g, b);  //красим точки
            gaphicTransformed->getImageRGB()->setPixel(points2.at(firstMinIndex).getX() + 1, points2.at(firstMinIndex).getY(), r, g, b);  //красим точки
            gaphicTransformed->getImageRGB()->setPixel(points2.at(firstMinIndex).getX(), points2.at(firstMinIndex).getY(), r, g, b);  //красим точки
            gaphicTransformed->getImageRGB()->setPixel(points2.at(firstMinIndex).getX(), points2.at(firstMinIndex).getY() - 1, r, g, b);  //красим точки
            gaphicTransformed->getImageRGB()->setPixel(points2.at(firstMinIndex).getX(), points2.at(firstMinIndex).getY() + 1, r, g, b);  //красим точки
        }
    }

//сохраняем
    myGraphic2->getImageRGB()->getImage()->save(path + "/res1.png");
    gaphicTransformed->getImageRGB()->getImage()->save(path + "/res2.png");



    myGraphic2->setImageFromRGB();   //переводим матрицу обратно в Image
    image = myGraphic2->getImage();

    myGraphic2->imageItem = myGraphic2->myScene->addPixmap(QPixmap::fromImage(*image));

    setInterfaceDisabled(false);
}


