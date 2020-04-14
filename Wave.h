//
// Created by AlinaArslanova on 29.03.2020.
//
#include <vector>
#include "Point.h"
#include "Cluster.h"
#include "Field.h"
#include <iostream>
#include <set>
#include <fstream>
#define PI 3.14159265

#ifndef UNTITLED1_WAVE_H
#define UNTITLED1_WAVE_H


class Wave {
public:
    Field f;
    int ID=0;
    int points_nmb;
    vector<vector<double>> a;
    int **b;
    vector<Cluster> clusters;

    double dist(Point q, Point p); //returns the distance between points

    void distance_matrix(); //build distance matrix between all points in the field

    void binary_matrix(double dt);


    void wave_alg(double dt); //waving algorithm

    void print_clusters(ofstream &out,string filename);

};


#endif //UNTITLED1_WAVE_H
