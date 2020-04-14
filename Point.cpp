
#include "cmath"
#include "Point.h"


Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

bool Point::operator==(Point b) {
    return (fabs(this->x - b.x) < eps && fabs(this->y - b.y) < eps);
}

Point Point::operator=(Point b) {
    this->x = b.x;
    this->y = b.y;
    return *this;
}

bool Point::operator!=(Point b) {
    return (fabs(this->x - b.x) >eps || fabs(this->y - b.y) >eps);
}

double Point::dist(Point b)
{
    return sqrt((this->x-b.x)*(this->x-b.x)+(this->y-b.y)*(this->y-b.y));
}