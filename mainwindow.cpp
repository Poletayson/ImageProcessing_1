#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfile.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
   connect(ui->buttonPyramides, SIGNAL(clicked()), this, SLOT(getPyramides()));

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
    #include <QDir>
    QString path = QApplication::applicationDirPath();  //QDir::currentPath();      //текущая директория
    if (QDir(path + "/Input").exists())
         path = path + "/Input";
    else
        QDir(path).mkdir("Input");
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

    myGraphic2->gaussianFilterRGBSep(static_cast<double>(ui->horizontalSlider->value()) / 3); //применяем фильтр Гаусса

    myGraphic2->setImageFromRGB();   //переводим матрицу обратно в Image
    image = myGraphic2->getImage();

    myGraphic2->imageItem = myGraphic2->myScene->addPixmap(QPixmap::fromImage(*image));
    setInterfaceDisabled(false);
}

void MainWindow::getPyramides()
{
    setInterfaceDisabled(true);

    delete image;

    myGraphic2->myScene->removeItem(myGraphic2->imageItem);
    delete myGraphic2->imageItem;

    myGraphic2->setImage(myGraphic->getImage());

    myGraphic2->getPyramids(ui->spinBoxOctavaCount->value(), ui->spinBoxLevelCount->value(), ui->horizontalSlider->value() / 3); //строим пирамиду

    myGraphic2->setImageFromRGB();   //переводим матрицу обратно в Image
    image = myGraphic2->getImage();


    myGraphic2->imageItem = myGraphic2->myScene->addPixmap(QPixmap::fromImage(*image));

    setInterfaceDisabled(false);
}


