#include "Point.h"
#include <vector>
#ifndef UNTITLED1_CLUSTER_H
#define UNTITLED1_CLUSTER_H



using namespace std;

class Cluster {
public:

    vector<Point> points;

    void add(Point p);
    vector<double> find_vectors();//function that finds
    Point find_mass_centre();
};



#endif //UNTITLED1_CLUSTER_H
