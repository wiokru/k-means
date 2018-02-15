#include "point.h"

Point::Point(double x, double y, string color){
    this->x = x;
    this->y = y;
    this->color = color;
    this->special.clear();
}

Point::Point(double x, double y, string color, string special){
    this->x = x;
    this->y = y;
    this->color = color;
    this->special = special;
}

string Point::pointToString(){
    string result;
    result = to_string(x)+" "+to_string(y)+" "+ color + " " + special + "\n";
    return result;
}

void Point::changeColor(string new_color){
    this->color = new_color;
}

string Point::getColor() const{
    return color;
}

double Point::getX() const{
    return x;
}

double Point::getY() const{
    return y;
}

string Point::getSpecial() const{
    return special;
}

void Point::setX(double value){
    x = value;
}

void Point::setY(double value){
    y = value;
}
