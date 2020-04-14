//
// Created by AlinaArslanova on 30.03.2020.
//
#include <vector>
#include "Point.h"
#include "Cluster.h"
#include "Field.h"
#include <iostream>
#include <fstream>
#define PI 3.14159265

#ifndef UNTITLED1_FOREL_H
#define UNTITLED1_FOREL_H


class Forel {
public:

    Field f;
    int ID=0;
    int points_nmb;
    vector<Cluster> clusters;
    Point mass_centre(vector<Point> points, vector<int> inside_circle);
    void forel (double r);
    vector<Point>forel_circles;
    double forel_r;
    void print_clusters(ofstream &out,string filename);



};


#endif //UNTITLED1_FOREL_H
