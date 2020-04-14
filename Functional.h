//
// Created by AlinaArslanova on 02.12.2019.
//
#include <string>
#include <vector>
#include "Field.h"

#include "Cluster.h"
#include "Wave.h"
#include "Dbscan.h"
#include "EM.h"
#include "Forel.h"
#include "Hierarchical.h"
#include "Kmean.h"
#include "Spanning_tree.h"

#ifndef UNTITLED1_FUNCTIONAL_H
#define UNTITLED1_FUNCTIONAL_H

#define PI 3.14159265

class Functional {
public:


    Field f;
    Dbscan dbscan_search;
    EM em_search;
    Forel forel_search;
    Hierarchical hierarchical_search;
    Kmean kmean_search;
    Spanning_tree span_tree_search;
    Wave wave_search;

    vector<vector<Cluster>> searches;
    void gnunorm(double xsr, double ysr, double dispx, double dispy, int count);

    void gnurnd(int min, int max, int count);

    void turn(int id, double alpha);

    void move(int id, double distx, double disty);

    void stretch(int id, double x_stretch, double y_stretch);


    void make_wave(double porog);

    void tree();

    void make_k(int k);

    void hierarchical(int k);

    void forel(double r);

    void dbscan(int min_point, double r);

    void em(int cl);





};


#endif //UNTITLED1_FUNCTIONAL_H
