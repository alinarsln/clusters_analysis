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
#ifndef UNTITLED1_EM_H
#define UNTITLED1_EM_H


class EM {
public:
    Field f;
    int ID=0;
    int points_nmb;
    int cl;
    vector<Cluster> clusters;
    vector<vector<Cluster>> clusters_for_film;

    vector<vector<double>> matrix_reversal(vector<vector<double>>a);
    vector<vector<double>>matrix_composition(vector<vector<double>> a ,vector<vector<double>> b);
    vector<vector<double>> matrix_transporation(vector<vector<double>>a);
    double determinat(vector<vector<double>> a);
    void em_alg(int cl);
    void make_clusters(  vector<vector<long double>>X,int cl);
    void make_film( ofstream &out,string filename);
    void print_clusters(ofstream &out,string filename);

};


#endif //UNTITLED1_EM_H
