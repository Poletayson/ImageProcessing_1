#ifndef INTERESTINGPOINT_H
#define INTERESTINGPOINT_H

#include "math.h"

#include "descriptor.h"

class InterestingPoint
{
public:
    InterestingPoint(int x, int y, double c);

    double getC() const;
    void setC(double value);

    int getX() const;

    int getY() const;

    static bool operatorLess (InterestingPoint p1, InterestingPoint p2);
    static bool operatorMore (InterestingPoint p1, InterestingPoint p2);

    static double getDistance (InterestingPoint a, InterestingPoint b);

    Descriptor getDescroptor() const;
    void setDescroptor(const Descriptor &value);

    double getAngle() const;
    void setAngle(double value);

private:
    int x, y;
    double c;   //значение
    double angle;   //угол

    Descriptor descroptor;
};

#endif // INTERESTINGPOINT_H
