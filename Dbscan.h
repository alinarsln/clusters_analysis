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
#ifndef UNTITLED1_DBSCAN_H
#define UNTITLED1_DBSCAN_H


class Dbscan {
public:
    Field f;
    int points_nmb;
    vector<int> neighbors(double r, Point x0);//finds neighbors of the point

    vector<int> make_unique(vector<int> points, vector<int> add_points);//makes unique the vector

    void dbscan(int min_point_nmb, double r);
    vector<Cluster>clusters;
    void print_clusters(ofstream &out,string filename);







};


#endif //UNTITLED1_DBSCAN_H
