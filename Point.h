

#ifndef UNTITLED1_POINT_H
#define UNTITLED1_POINT_H


class Point {
public:
    const double eps = 0.0001;
    double x, y;

    bool operator==(Point b);
    Point operator= (Point b);
    bool operator!=(Point b);
    Point(double x, double y);
};

#endif //UNTITLED1_POINT_H
