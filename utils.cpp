#include "utils.h"

Utils::Utils()
{

}

//расстояние между точками
double Utils::getDistance(double x0, double y0, double x1, double y1)
{
    return sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2));
}

//расстояние между дескрипторами
double Utils::getDescriptorDistance(Descriptor d1, Descriptor d2)
{
    double result = 0;
    int histogramsCount = d1.getHistogramsCount();
    int basketCount = d1.getBascketCount();
    for(int i = 0; i < histogramsCount; i++){
        for(int j = 0; j < basketCount; j++){
            result += pow((d1.getBin(i,j) - d2.getBin(i,j)), 2);
        }
    }
    return sqrt(result);
}
