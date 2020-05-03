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

//    //находим ядро Гаусса
//    double sigma = static_cast<double>(gridSize) / 6;
//    int halfSize = gridSize / 2;
//    gaussKernel = new double[gridSize * gridSize];

//    double coeff = 1 / (2 * M_PI * sigma * sigma);
//    double delitel = 2 * sigma * sigma;

//    for (int u = -halfSize; u <= halfSize; u++)
//        for (int v = -halfSize; v <= halfSize; v++){
//            gaussKernel[(u + halfSize) * halfSize + (v  + halfSize)] = coeff * exp(- (u * u + v * v) / delitel);
////            qDebug() << gaussKernel[(u + halfSize) * halfSize + (v  + halfSize)];
//        }
}

Descriptor DescriptorConstructor::createDescriptor(InterestingPoint inputPoint)
{
    Descriptor descriptor (basketCount, histogramCount); //дескриптор
    double basketSize = 360.0 / basketCount;   //размер одной корзины
    int descriptorRadius = gridSize / 2;

    int x = inputPoint.getX();
    int y = inputPoint.getY();

    for(int i = -descriptorRadius; i < descriptorRadius; i++){
        for(int j = -descriptorRadius; j < descriptorRadius; j++){

            //Учитываем угол особой точки
            int angledX = (i * cos((360.0 - inputPoint.getAngle()) * M_PI / 180.0) - j * sin((360.0 - inputPoint.getAngle()) * M_PI / 180.0) + 0.5);
            int angledY = (i * sin((360.0 - inputPoint.getAngle()) * M_PI / 180.0) + j * cos((360.0 - inputPoint.getAngle()) * M_PI / 180.0) + 0.5);

            //За границей?
            if(angledX < -descriptorRadius) {
                angledX = 0;
            }
            else {
                if(angledX >= descriptorRadius) {
                    angledX = descriptorRadius -1;
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
                    angledY = descriptorRadius -1;
                }
                else {
                    angledY += descriptorRadius;
                }
            }


            double localDirection =  gradientDirection->getPixel(x + i, y + j) - inputPoint.getAngle(); //направление градиента. Учитываем направление угла

            //Приводим к интервалу 0..360
            localDirection = (localDirection < 0) ? localDirection + 360 : localDirection;
            localDirection = (localDirection > 360) ? localDirection - 360 : localDirection;
///
//                //Текущий х у
//                int x = angledX / ((descriptorRadius * 2) / histogramCount) - 0.5;
//                int y = angledY / ((descriptorRadius * 2) / histogramCount) - 0.5;


            //Номер гистограммы
            int histogramNumber = (static_cast<double> (angledY * gridSize + angledX) / static_cast<double>(gridSize * gridSize)) * histogramCount * histogramCount;
            //qDebug() << "angledX: " << angledX << " angledY: " << angledY << " hn: " << histogramNumber;

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
            descriptor.setBin(histogramNumber, binNumber,  gradient->getPixel(inputPoint.getX() + i, inputPoint.getY() + j) * (1 - currentCenterDistance / basketSize));
            descriptor.setBin(histogramNumber, relatedBin, gradient->getPixel(inputPoint.getX() + i, inputPoint.getY() + j) * (1 - relatedCenterDistance / basketSize));
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

        for(int i = -descriptorRadius; i < descriptorRadius; i++){
            for(int j = -descriptorRadius; j < descriptorRadius; j++){

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

                    localBaskets[basketNumber] += gradient->getPixel(points.at(index).getX() + i, points.at(index).getY() + j) * (1 - thisCenterDistance / localBasketSize);
                    localBaskets[relatedbasketNumber] += gradient->getPixel(points.at(index).getX() + i, points.at(index).getY() + j) * (1 - relatedCenterDistance / localBasketSize);
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
            }
        }

        //добавили первую
        InterestingPoint firstPoint(points.at(index));
        firstPoint.setAngle((double)firstMaxIndex * localBasketSize);
        orientPoints.push_back(firstPoint);

        //если есть корзины >= 0.8 от макс значения, то добваляем их тоже
//        for(int i = 0; i < localBasketCount; i++){
            if(secondMaxValue >= (firstMaxValue * 0.8)){
                InterestingPoint otherPoint(points.at(index));
                otherPoint.setAngle ((double)secondMaxIndex * localBasketSize);
                orientPoints.push_back(otherPoint);
            }

//        }

    }
    return orientPoints;
}
