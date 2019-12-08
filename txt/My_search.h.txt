#include <vector>
#include "Point.h"
#include "Cluster.h"
#include "Field.h"
#include <iostream>
#include <fstream>
#ifndef UNTITLED1_MY_SEARCH_H
#define UNTITLED1_MY_SEARCH_H


class My_Search {
public:
    Field f;
    int points_nmb;
    vector<vector<double>> a;
    int **b;
    int k;
    vector<Cluster> clusters;
    vector<double> tree_length;
    vector<pair<Point, Point>> tree_edges;


    double dist(Point q, Point p);

    void distance_matrix();

    void binary_matrix(double dt);

    void print_matrix() {

        ofstream gnu("distance_matrix.txt");
        for (int i = 0; i < points_nmb; i++) {
            for (int j = 0; j < points_nmb; j++) {
                gnu << a[i][j] << " ";

            }
            gnu << endl;
        }

    }

    void wave(double dt);

    vector<Point> centres;
    vector<Point> old_centres;
    vector<Point> new_centres;
    vector<pair<Point,Point>> denrdogramm;
    vector <Point> h_centres;

    void make_first_centers();

    void iteration();

    void k_mean();

    void spanning_tree();

    Point mass_centre(vector<Point> points, vector<int> inside_circle);


    void change_matrix(int c, int d, Point p, vector<Point> all_points);

    void hierarchical(int k_last);


    void forel(double r);


    vector<int> neighbors(double r, Point x0);

    vector<int> make_unique(vector<int> points, vector<int> add_points);

    void dbscan(int min_point_nmb, double r);
};


#endif //UNTITLED1_MY_SEARCH_H
