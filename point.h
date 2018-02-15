#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <string>

using namespace std;

class Point
{
    double x;
    double y;
    string color;
    string special;
    //bool special; ???

public:
    Point(double x, double y, string color);
    Point(double x, double y, string color, string special);
    string pointToString();
    void changeColor(string new_color);
    string getColor() const;
    double getX() const;
    double getY() const;
    string getSpecial() const;
    void setX(double value);
    void setY(double value);
};

#endif // POINT_H
