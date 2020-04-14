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


#ifndef UNTITLED1_SPANNING_TREE_H
#define UNTITLED1_SPANNING_TREE_H


class Spanning_tree {
public:
    Field f;
    int ID=0;
    int points_nmb;
    vector<vector<double>> a;
    vector<Cluster> clusters;
    int k;

    vector<double> tree_length;
    vector<pair<Point, Point>> tree_edges;
    void distance_matrix();
    void spanning_tree();
    void print_tree(ofstream &out,string filename);
};


#endif //UNTITLED1_SPANNING_TREE_H
