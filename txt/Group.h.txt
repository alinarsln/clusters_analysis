
#include <vector>
#include <cmath>
#include <random>
#include "Point.h"

using namespace std;

#ifndef UNTITLED1_GROUP_H
#define UNTITLED1_GROUP_H


class Group {
public:
    vector<Point> points;

    void add(Point p);

    void make_group(double xsr, double ysr, double dispx, double dispy, int count);

};


#endif //UNTITLED1_GROUP_H
