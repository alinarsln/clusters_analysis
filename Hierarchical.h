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
#ifndef UNTITLED1_HIERARCHICAL_H
#define UNTITLED1_HIERARCHICAL_H


class Hierarchical {
public:
    Field f;
    int ID=0;
    int points_nmb;
    vector<Cluster> clusters;
    vector<vector<double>> a;
    int k;
    void distance_matrix();
    void change_matrix(int c, int d,  vector<Point> all_points); //deletes the row and columns

    void hierarchical(int k_last); //hierarchical algorithm
    void print_clusters(ofstream &out,string filename);


};


#endif //UNTITLED1_HIERARCHICAL_H
