
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

    void print_clusters(ofstream& out);
    void print_tree(ofstream& out);
    void print_tree_length(ofstream& out);
    void load_groups(ifstream &in);

    void print_groups(ofstream& out);
    void print_clusters_for_hier(ofstream& out);
    int points_saved=0;
    istream* in;
    string a;




};


#endif //UNTITLED1_INTERFACE_H
