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

#ifndef UNTITLED1_KMEAN_H
#define UNTITLED1_KMEAN_H


class Kmean {
public:
    Field f;
    int ID=0;
    int points_nmb;
    vector<Cluster> clusters;
    int k;

    vector<Point> centres;
    vector<Point> old_centres;
    vector<Point> new_centres;

    void make_first_centers(); //first centres for k_mean iteration

    void iteration(); //iteration for kmean

    void k_mean();//kmean algorithm, compare whether the centres are balanced
    void print_clusters(ofstream &out,string filename);

};


#endif //UNTITLED1_KMEAN_H
