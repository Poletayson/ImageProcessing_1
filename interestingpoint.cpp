#include "interestingpoint.h"


InterestingPoint::InterestingPoint(int x, int y, double c)
{
    this->x = x;
    this->y = y;
    this->c = c;
    angle = 0;
}

double InterestingPoint::getC() const
{
    return c;
}

void InterestingPoint::setC(double value)
{
    c = value;
}

int InterestingPoint::getX() const
{
    return x;
}

int InterestingPoint::getY() const
{
    return y;
}

bool InterestingPoint::operatorLess(InterestingPoint p1, InterestingPoint p2)
{
    if (p1.getC() < p2.getC())
        return true;
    else
        return false;
}

bool InterestingPoint::operatorMore(InterestingPoint p1, InterestingPoint p2)
{
    if (p1.getC() > p2.getC())
        return true;
    else
        return false;
}

//расстояние между точками
double InterestingPoint::getDistance(InterestingPoint a, InterestingPoint b)
{
    double xd = a.getX() - b.getX();
    double yd = a.getY() - b.getY();
    return  sqrt(xd * xd + yd * yd);
}

Descriptor InterestingPoint::getDescroptor() const
{
    return descroptor;
}

void InterestingPoint::setDescroptor(const Descriptor &value)
{
    descroptor = value;
}

double InterestingPoint::getAngle() const
{
    return angle;
}

void InterestingPoint::setAngle(double value)
{
    angle = value;
}
