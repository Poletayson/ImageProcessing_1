#ifndef INTERESTINGPOINT_H
#define INTERESTINGPOINT_H


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

private:
    int x, y;
    double c;
};

#endif // INTERESTINGPOINT_H
