
#include "Functional.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#ifndef UNTITLED1_INTERFACE_H
#define UNTITLED1_INTERFACE_H


class Interface {
    string  b;
    Functional plane;
    ofstream out;
    ofstream logout;

public:

    ifstream input;
    bool if_file;
    void start();

    void log(string s);
    void command();


    void print_tree(ofstream& out,vector<pair<Point,Point>> tree_edges);//printing a tree
    void print_tree_length(ofstream& out, vector<double> tree_length);//output the length of the tree to file
    void load_groups(ifstream &in);//loads generated points

    void print_groups(ofstream& out);//prints generated points
    void print_clusters_for_hier(ofstream& out,vector<pair<Point,Point>> dendrogramm);//prints the middle point
    int points_saved=0;
    istream* in;
    string a;



};


#endif //UNTITLED1_INTERFACE_H
