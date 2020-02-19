#include "mainwindow.h"
#include <QApplication>
#include <iostream>



int main(int argc, char *argv[])
{

    setlocale(LC_ALL, "rus");
    //std::cout<<"Args: "<<argv[0]<<argv[1]<<argv[2]<<argv[3];



    //MPI_Init(nullptr, nullptr);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
