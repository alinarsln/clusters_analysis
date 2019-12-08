

#include "Functional.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include "Interface.h"
#include <fstream>

void Interface::start()
{
    cout<<"Enter 1 to read commands from file  or enter 0 to read from console:";
    string a;

    while(1) {
        cin>>a;
        if (a == "1") {
            if_file=1;

            string filename;
            cout << "Enter filename:" << endl;
            cin >> filename;
            input.open(filename);
            if (!input.is_open())
                cout << "Error in opening the file ";
            break;
        } else if (a == "0") {
            if_file=0;
            cout << "Enter commands here:" << endl;
            break;
        } else cout << "Enter 1 or 0: " << endl;
    }
    command();
}
void Interface::log(string s)
{
    logout<<s<<endl;
    if (!if_file)
        cout<<s<<endl;
}

void Interface::command() {

    if (if_file) {
        in = &input;

    } else {
        in = &cin;
    }
    logout.open("logout.txt");
    ifstream help("help.txt");

    while(1){

        *in >> a;
        if (a.find_first_of("//") == 0) continue;
        if (a == "exit") {
            if (!points_saved) {
                ofstream points_save;
                points_save.open("points_lastsave.txt");
                print_groups(points_save);
                log("all values saved at points_lastsave.txt");
            }
            logout.close();
            out.close();
            break;

        }
        if (a == "random points") {
            int n;
            double _min,_max;
            *in >> _min >> _max>>n;
            plane.gnurnd(_min,_max,n);
        } else if (a == "create_group") {
            int n;
            double xsr,ysr,dispx,dispy;
            *in >> xsr >> ysr >> dispx >> dispy >> n;
            plane.gnunorm(xsr, ysr, dispx, dispy, n);
            log(" group is made with n = " + to_string(n) + " xsr = " + to_string(xsr) + " ysr = " + to_string(ysr) + " dispx = "
                + to_string(dispx) + " dispy = " + to_string(dispy)+" id="+to_string(plane.f.groups.size()-1) );

        }  else if (a == "help") {
            while (!help.eof()) {
                getline(help, b);
                cout << b << endl;
            }
        } else if (a == "turn") {
            int id;
            double alpha;
            *in >> id>>alpha;
            log("group is added and turned "+to_string(alpha)+" degrees id="+to_string(plane.f.groups.size()-1));
            plane.turn(id, alpha);
        } else if (a == "kmean") {
            int k;
            *in >> k;
            plane.make_k(k);
            log("found clusters by k-mean algorithm and k="+to_string(k));
        } else if (a == "wave") {
            double porog;
            *in >> porog;
            plane.make_wave(porog);
            log("found clusters by wave algorithm and treshold value="+to_string(porog));
        } else if (a == "move") {
            int id;
            double x,y;
            *in >> id>>x>>y;
            plane.move(id, x, y);
            log("group is added and moved  "+to_string(x)+" on the x axis and  "+ to_string(y)+" on the y axis id="+to_string(plane.f.groups.size()-1));

        } else if (a == "stretch") {
            int id;
            double x,y;
            *in >> id>>x>>y;
            plane.stretch(id, x, y);
            log("group is added and stretched  "+to_string(x)+" on the x axis and  "+ to_string(y)+" on the y axis id="+to_string(plane.f.groups.size()-1));
        } else if (a == "tree") {
            plane.tree();
            log("tree is made   ");
        } else if (a == "forel") {
            double r;
            *in >> r;
            plane.forel(r);
            log("found clusters by FOREL algorithm and radius="+to_string(r));
        } else if (a == "hierarchical") {
            int k;
            *in >> k;
            plane.hierarchical(k);
            log( "found clusters by hierarchical algorithm and k="+to_string(k));
        } else if (a == "dbscan") {
            int min_point;
            double r;
            *in >> min_point>>r;
            plane.dbscan(min_point, r);
            log("found clusters by dbscan algorithm and radius= "+to_string(r)+ " min_point that form a dense area "+to_string(min_point));
        }else if (a == "print_clusters") {
            string filename;
            *in >> filename;
            ofstream out_gnu;
            string filename_gnu = filename.substr(0, filename.find_last_of('.')) + "_gnu.plt";
            out_gnu.open(filename_gnu);
            out_gnu << "rgb(r,g,b) = 65536 * int(r) + 256 * int(g) + int(b)"<<endl;
            out_gnu << "plot '/Users/AlinaArslanova/untitled1/cmake-build-debug/" + filename + "' using 1:2:(rgb($3,$4,$5))  notitle with points lc rgb variable ";
            out.open(filename);
            log("printing clusters to " + filename);
            print_clusters(out);
            out.close();
            out_gnu.close();
        }else if (a == "print_tree") {
            string filename;
            *in >> filename;
            ofstream out;
            ofstream out_gnu;
            string filename_gnu = filename.substr(0, filename.find_last_of('.')) + "_gnu.plt";
            out_gnu.open(filename_gnu);
            out_gnu << "plot '/Users/AlinaArslanova/untitled1/cmake-build-debug/"<<filename<<"'  u 1:2 with lines lc rgb \"black\" lw 2 notitle"<<endl;
            out.open( filename);
            log("printing spanning tree to " + filename);
            print_tree(out);
            out.close();
            out_gnu.close();
        }else if (a == "print_for_hierarchical") {
            string filename;
            *in >> filename;
            ofstream out;
            ofstream out_gnu;
            string filename_gnu = filename.substr(0, filename.find_last_of('.')) + "_gnu.plt";//w l lc rgb 'dark-red' lw 2
            out_gnu.open(filename_gnu);
            out_gnu << "rgb(r,g,b) = 65536 * int(r) + 256 * int(g) + int(b)"<<endl;
            out_gnu << "plot '/Users/AlinaArslanova/untitled1/cmake-build-debug/"<<filename<<
            "'using 1:2:(rgb($3,$4,$5)) w linespoints pt 7 ps 0.3 lw 1 lc rgb variable notitle ";
            out.open( filename);
            log("printing for hierarchical  to " + filename);
            print_clusters_for_hier(out);
            out.close();
            out_gnu.close();

        }
        else if (a =="print_tree_histagram") {
            string filename;
            *in >> filename;
            ofstream out;
            ofstream out_gnu;
            string filename_gnu = "out/" + filename.substr(0, filename.find_last_of('.')) + "_gnu.plt";
            out_gnu.open(filename_gnu);
            out.open("out/" + filename);
            print_tree_length( out);

            out_gnu << ("binwidth=0.1\n"
                        "bin(x,width)=width*floor(x/width) + width/2.0\n"
                        "set boxwidth binwidth\n"
                        "plot '"+filename+"' using (bin($1,binwidth)):(1.0) smooth freq with boxes");

            log("printing spanning tree histagram to out/" + filename);
            out.close();
            out_gnu.close();
        }
        else if (a == "load") {
            string filename;
            *in >> filename;
            ifstream in_points;
            if (filename == "-1") {
                in_points.open("points_lastsave.txt");
                filename = "points_lastsave.txt";
            } else {
                in_points.open(filename);
            }
            log("reading points from " + filename);
            load_groups(in_points);
            in_points.close();
        } else if (a == "save_points") {
            string filename;
            *in >> filename;
            log("saving points to " + filename);
            ofstream points_save;
            points_save.open(filename);
            print_groups(points_save);
            points_save.close();
            points_saved = 1;
        }
        else cout<<a<<" command not found ";
    }

}
void Interface:: print_clusters(ofstream& out)
{
    int a, b, c;
    if (!out.is_open()) {
        cout << "Errors in opening" << endl;
    } else {

        for (int i = 0; i < (int)plane.search.clusters.size(); i++) {

            a = rand() % 257;
            b = rand() % 257;
            c = rand() % 257;
            Cluster g = plane.search.clusters[i];
            for (int j = 0; j < (int) g.points.size(); j++) {

                out << g.points[j].x << " " << g.points[j].y << " " << a << " " << b << " "<< c << " " << endl;
            }


        }

        out.close();
    }

}
void Interface:: print_clusters_for_hier(ofstream& out)
{

    for(int i=0;i<plane.search.denrdogramm.size();i++)
    {

        out<<plane.search.denrdogramm[i].first.x<< " "<<plane.search.denrdogramm[i].first.y<<" 8 43 116  "<<endl;
        out<<plane.search.denrdogramm[i].second.x<< " "<<plane.search.denrdogramm[i].second.y<<" 28 229 68  "<<endl;
        out<<endl;


    }

}
void Interface::print_tree(ofstream& out)
{
    for(int i=0;i<plane.search.tree_edges.size();i++)
    {

        out<<plane.search.tree_edges[i].first.x<< " "<<plane.search.tree_edges[i].first.y<<endl;
        out<<plane.search.tree_edges[i].second.x<< " "<<plane.search.tree_edges[i].second.y<<endl;
        out<<endl;

    }

}
void Interface:: print_tree_length(ofstream& out)
{
    for(int i=0;i<plane.search.tree_length.size();i++)
    {

        out<<plane.search.tree_length[i]<<endl;

    }

}
void Interface:: load_groups(ifstream &in) {
    vector<Group> groups;
    plane.f.groups.clear();
    plane.f.all_points.clear();
    double x, y;
    int a, b, c, a1 = 0, b1 = 0, c1 = 0;

    in >> x >> y >> a >> b >> c;
    a1 = a;
    b1 = b;
    c1 = c;
    while (!in.eof()) {
        Group g;
        g.points.push_back(Point(x, y));
        a = a1;
        b = b1;
        c = c1;
        while (a == a1 && b == b1 && c == c1) {
            in >> x >> y >> a1 >> b1 >> c1;
            if (a == a1 && b == b1 && c == c1 && !in.eof()) {
                Point p(x, y);
                g.points.push_back(p);
            } else {
                break;
            }

        }
        plane.f.add(g);
    }
}
void Interface::print_groups(ofstream& out)
{
    int a, b, c;
    if (!out.is_open()) {
        cout << "Errors in opening" << endl;
    } else {

        for (int i = 0; i < (int) plane.f.groups.size(); i++) {

            a = rand() % 257;
            b = rand() % 257;
            c = rand() % 257;
            Group g = plane.f.groups[i];
            for (int j = 0; j < (int) g.points.size(); j++) {

                out << g.points[j].x << " " << g.points[j].y << " " << a << " " << b << " " << c
                    << " " << endl;
            }


        }
        out.close();
    }

}