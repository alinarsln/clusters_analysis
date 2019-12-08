//
// Created by AlinaArslanova on 02.12.2019.
//
#include <string>
#include <vector>
#include "Field.h"
#include "My_search.h"

#ifndef UNTITLED1_FUNCTIONAL_H
#define UNTITLED1_FUNCTIONAL_H

#define PI 3.14159265

class Functional {
public:


    Field f;
    My_Search search;

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


};


#endif //UNTITLED1_FUNCTIONAL_H
