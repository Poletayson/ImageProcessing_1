#include "descriptorconstructor.h"

DescriptorConstructor::DescriptorConstructor(DoubleImageMono *image, int basketCountP, int histCountP, int gridSizeP)
{
    int w = image->getWidth();
    int h = image->getHeight();

    basketCount = basketCountP;
    histogramCount = histCountP;
    gridSize = gridSizeP;

    //находим градиент
    gradient = new DoubleImageMono(image->getImageDouble(), w, h);
    gradient->setGradient();
    gradient->setEffect(DoubleImageMono::EDGE_BLACK);

    //находим производные
    dx = new DoubleImageMono(image->getImageDouble(), w, h);
    dy = new DoubleImageMono(image->getImageDouble(), w, h);
    dx->setDerivateX();
    dy->setDerivateY();

    //находим направление градиента
    gradientDirection = new DoubleImageMono(image->getImageDouble(), w, h);
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            double gradDir = atan2(dy->getPixel(i, j), dx->getPixel(i, j)) * 180.0 / M_PI + 180.0;  //у нас угол в градусах, 0..360
            gradientDirection->setPixel(i, j, gradDir);

            //qDebug() << L1 << " " << L2;
        }
    }
//    gradientDirection->save("/gradientDirection.png");

    //находим ядро Гаусса
    double sigma = static_cast<double>(gridSize) / 6;
    int halfSize = gridSize / 2;
    gaussKernel = new double[(gridSize + 1) * (gridSize + 1)];

    double coeff = 1 / (2 * M_PI * sigma * sigma);
    double delitel = 2 * sigma * sigma;

    for (int u = -halfSize; u <= halfSize; u++){
//        qDebug() << "";
        for (int v = -halfSize; v <= halfSize; v++){
            gaussKernel[(u + halfSize) * gridSize + (v  + halfSize)] = coeff * exp(- (u * u + v * v) / delitel);
//            qDebug() << gaussKernel[(u + halfSize) * gridSize + (v  + halfSize)];
        }
    }
}

Descriptor DescriptorConstructor::createDescriptor(InterestingPoint inputPoint)
{
    Descriptor descriptor (basketCount, histogramCount); //дескриптор
    double basketSize = 360.0 / basketCount;   //размер одной корзины
    int descriptorRadius = gridSize / 2;

//    int x = inputPoint.getX();
//    int y = inputPoint.getY();

    for(int i = -descriptorRadius; i < descriptorRadius; i++){
        for(int j = -descriptorRadius; j < descriptorRadius; j++){

            //Учитываем угол особой точки
            int angledX = (i * cos((360.0 - inputPoint.getAngle()) * M_PI / 180.0) - j * sin((360.0 - inputPoint.getAngle()) * M_PI / 180.0) + 0.5);
            int angledY = (i * sin((360.0 - inputPoint.getAngle()) * M_PI / 180.0) + j * cos((360.0 - inputPoint.getAngle()) * M_PI / 180.0) + 0.5);

//            //В пределах дескриптора?
//            if(Utils::getDistance((double)angledX, (double)angledY, 0.0, 0.0) < sqrt(pow(descriptorRadius,2) + pow(descriptorRadius,2))){


        if(Utils::getDistance((double)angledX, (double)angledY, 0.0, 0.0) > sqrt(pow(descriptorRadius,2) + pow(descriptorRadius,2))){
            double angle = atan2(angledY, angledX ); //угол, образуемый отрезком
            qDebug() << "!!!NO!!!" << " " << inputPoint.getX() << " " << inputPoint.getY() << " " << i << " " << j << " " << angledX << " " << angledY << " " << angle << " " << static_cast<int>(sin(angle) * qMax(angledX - 8, 0) + 0.5) << " " << static_cast<int>(cos(angle) * qMax(angledY - 8, 0) + 0.5);
        //    angledY += static_cast<int>(sin(angle) * qMax(angledX - 8, 0) + 0.5) ;
        //    angledX += static_cast<int>(cos(angle) * qMax(angledY - 8, 0) + 0.5);
        }



            double angle = atan2(angledY, angledX ); //угол, образуемый отрезком
            angledY -= static_cast<int>(sin(angle) * qMax(angledX - 8, 0) + 0.5);
            angledX -= static_cast<int>(cos(angle) * qMax(angledY - 8, 0) + 0.5);

                //За границей?
                if(angledX < -descriptorRadius) {
                    angledX = 0;
                }
                else {
                    if(angledX >= descriptorRadius) {


                        angledX = descriptorRadius;
                    }
                    else {
                        angledX += descriptorRadius;
                    }
                }

                if(angledY < -descriptorRadius) {
                    angledY = 0;
                }
                else {
                    if(angledY >= descriptorRadius) {
                        angledY = descriptorRadius;
                    }
                    else {
                        angledY += descriptorRadius;
                    }
                }


                double localDirection =  gradientDirection->getPixel(inputPoint.getX() + i, inputPoint.getY() + j) - inputPoint.getAngle(); //направление градиента. Учитываем направление угла
                //Приводим к интервалу 0..360
                localDirection = (localDirection < 0) ? localDirection + 360 : localDirection;
                localDirection = (localDirection > 360) ? localDirection - 360 : localDirection;

                //х у гистограммы, начиная с 0
                int x = static_cast<double>(angledX) / (static_cast<double>(descriptorRadius * 2) / histogramCount) - 0.2;
                int y = static_cast<double>(angledY) / (static_cast<double>(descriptorRadius * 2) / histogramCount) - 0.2;


                //Номер гистограммы
                int histogramNumber = static_cast<double> (y * histogramCount + x);// / static_cast<double>(gridSize * gridSize)) * histogramCount * histogramCount;
//                qDebug() << "i: " << i << " j: " << j<< "angledX: " << angledX << " angledY: " << angledY << " angle: " << inputPoint.getAngle() << " hn: " << histogramNumber;

                //Раскидываем по корзинам
                int binNumber = (localDirection / basketSize + 0.5);   //Номер корзины
                if (binNumber == basketCount)
                    binNumber--;

                double localBinCenter = (double)binNumber * basketSize + basketSize / 2.0;    //центр корзины

                int relatedBin; //Номер связанной корзины - той, к которой тоже добавим
                if(localDirection < localBinCenter)
                    relatedBin = (binNumber - 1) == -1 ? basketCount - 1 : binNumber - 1;
                else
                    relatedBin = (binNumber + 1) == basketCount ? 0 : binNumber + 1;

                double currentCenterDistance = abs(localBinCenter - localDirection);
                double relatedCenterDistance = basketSize - currentCenterDistance;


                //добавляем в корзины значения
                descriptor.setBin(histogramNumber, binNumber, descriptor.getBin(histogramNumber, binNumber) + gradient->getPixel(inputPoint.getX() + i, inputPoint.getY() + j) * (1 - currentCenterDistance / basketSize));
                descriptor.setBin(histogramNumber, relatedBin, descriptor.getBin(histogramNumber, relatedBin) + gradient->getPixel(inputPoint.getX() + i, inputPoint.getY() + j) * (1 - relatedCenterDistance / basketSize));
//            }
//            else {
//                double angle = atan2(angledY, angledX ); //угол, образуемый отрезком
//                qDebug() << "!!!NO!!!" << " " << inputPoint.getX() << " " << inputPoint.getY() << " " << i << " " << j << " " << angledX << " " << angledY << " " << angle << " " << sin(angle) * qMax(angledX - 7, 0);
//            }

        }
    }
    descriptor.normalize(); //нормализуем
    return descriptor;
}

QList<InterestingPoint> DescriptorConstructor::orientPoints(QList<InterestingPoint> points)
{
    QList<InterestingPoint> orientPoints;

    int localBasketCount = 36;  //число корзин
    double localBasketSize = 360.0 / localBasketCount;  //охват корзины
    int descriptorRadius = gridSize / 2;    //радиус дескриптора

    for(int index = 0; index < points.size(); index++) {

        double localBaskets[localBasketCount];
        for (int i = 0; i < localBasketCount; i++){
            localBaskets[i] = 0;
        }

        for(int i = -descriptorRadius; i <= descriptorRadius; i++){
            for(int j = -descriptorRadius; j <= descriptorRadius; j++){

                //В пределах ?
                if(Utils::getDistance((double)i, (double)j, 0.0,0.0) < sqrt(pow(descriptorRadius,2) + pow(descriptorRadius,2))){

                    //Направление Фи
                    double direction =  gradientDirection->getPixel(points.at(index).getX() + i, points.at(index).getY() + j);

                    //Номер корзины
                    int basketNumber = static_cast<int> (direction / localBasketSize + 0.5);

                    //Раскидываем по корзинам
                    double localBinCenter = (double)basketNumber * localBasketSize + localBasketSize / 2.0;

                    int relatedbasketNumber;
                    if(direction < localBinCenter)
                        relatedbasketNumber = basketNumber - 1;
                    else
                        relatedbasketNumber = basketNumber + 1;

                    if (relatedbasketNumber < 0)
                        relatedbasketNumber = localBasketCount - 1;
                    if (relatedbasketNumber > localBasketCount - 1)
                        relatedbasketNumber = 0;


                    double thisCenterDistance = abs(localBinCenter - direction);    //расстояния от направления Фи до центров корзин
                    double relatedCenterDistance = localBasketSize - thisCenterDistance;

                    localBaskets[basketNumber] += gradient->getPixel(points.at(index).getX() + i, points.at(index).getY() + j) * (1 - thisCenterDistance / localBasketSize) * gaussKernel[(i + descriptorRadius) * gridSize + (j  + descriptorRadius)];
                    localBaskets[relatedbasketNumber] += gradient->getPixel(points.at(index).getX() + i, points.at(index).getY() + j) * (1 - relatedCenterDistance / localBasketSize) * gaussKernel[(i + descriptorRadius) * gridSize + (j  + descriptorRadius)];
                }
            }
        }

        double firstMaxValue = -1;
        int firstMaxIndex = -1;
        double secondMaxValue = -1;
        int secondMaxIndex = -1;

        //Нашли первую и вторую максимальную
        for(int i = 0; i < localBasketCount; i++){
            if(localBaskets[i] > firstMaxValue){
                secondMaxValue = firstMaxValue;
                secondMaxIndex = firstMaxIndex;

                firstMaxValue = localBaskets[i];
                firstMaxIndex = i;
            } else {
                if(localBaskets[i] > secondMaxValue){
                    secondMaxValue = localBaskets[i];
                    secondMaxIndex = i;
                }
            }
        }

        //добавили первую
        InterestingPoint firstPoint(points.at(index));
        firstPoint.setAngle(static_cast<double>(firstMaxIndex * localBasketSize));
        orientPoints.push_back(firstPoint);
//        qDebug()<<QString("");
//        qDebug()<<QString::number(firstPoint.getX()) + " " + QString::number(firstPoint.getY()) + " " + QString::number(firstPoint.getAngle());

        //если вторая корзина >= 0.8 от макс значения, то добваляем ее тоже
        if(secondMaxValue >= (firstMaxValue * 0.8)){
            InterestingPoint otherPoint(points.at(index));
            otherPoint.setAngle (static_cast<double>(secondMaxIndex * localBasketSize));
            orientPoints.push_back(otherPoint);
//            qDebug()<<QString::number(otherPoint.getX()) + " " + QString::number(otherPoint.getY()) + " " + QString::number(otherPoint.getAngle());
        }

    }
    return orientPoints;
}
