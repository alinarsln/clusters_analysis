//
// Created by AlinaArslanova on 30.03.2020.
//

#include "Dbscan.h"


vector<int> Dbscan::neighbors(double r, Point x0) {
    vector<int> neighbors;
    for (int i = 0; i < (int) f.all_points.size(); i++) {
        if (f.all_points[i].dist(x0)  <= r && (f.all_points[i].dist(x0)) >= 0) {
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

vector<int> Dbscan::make_unique(vector<int> points, vector<int> add_points) {
    vector<int> t;
    for (int i = 0; i < (int) add_points.size(); i++) {
        bool u = false;
        for (int j = 0; j < (int) points.size(); j++) {
            if (add_points[i] == points[j]) {
                u = true;
                break;
            }

        }
        if (u == false) {
            t.push_back(add_points[i]);
        }
    }
    for (int i = 0; i < (int) t.size(); i++)
        points.push_back(t[i]);
    return points;
}

void Dbscan::dbscan(int min_point_nmb, double r) {
    clusters.clear();
    vector<int> label(points_nmb, 0);//0-not used,-1-noise,others-number of cluster//
    vector<int> n;//vector of neighbors researched point
    vector<int> s;//vector of neighbors of neighbors of researched point;
    vector<int> t;
    int c = 0;//for clusters
    for (int i = 0; i < points_nmb; i++) {

        if (label[i] == 0) {
            n.clear();
            n = neighbors(r, f.all_points[i]);//neighbors in cluster
            //n.insert(n.begin(),neighbors(r,f.all_points[i]).begin(),neighbors(r,f.all_points[i]).end());
            if ((int) n.size() < min_point_nmb - 1) {
                label[i] = -1;//it's noise-separate cluster
            } else {
                Cluster cluster;
                c++;
                cluster.points.push_back(f.all_points[i]);
                label[i] = c;
                for (int j = 0; j < (int) n.size(); j++) {
                    if (label[n[j]] == 0) {
                        cluster.points.push_back(f.all_points[n[j]]);
                        s.clear();
                        s = neighbors(r, f.all_points[n[j]]);
                        if ((int) s.size() >= min_point_nmb - 1) {
                            label[n[j]] = c;
                            n = make_unique(n, s);
                        } else label[n[j]] = -1;

                    }
                    if (label[n[j]] == -1) {
                        label[n[j]] = c;
                        cluster.points.push_back(f.all_points[n[j]]);
                    }

                }
                clusters.push_back(cluster);
            }


        }


    }
    for (int i = 0; i < points_nmb; i++) {
        if (label[i] == -1) {
            Cluster cluster;
            cluster.points.push_back(f.all_points[i]);
            clusters.push_back(cluster);
        }
    }

}

void Dbscan::print_clusters(ofstream &out,string filename) {
    ofstream out_gnu;
    ofstream out_arrow;
    string arrow_name=filename.substr(0, filename.find_last_of('.')) + "_arrow";
    string filename_gnu = filename.substr(0, filename.find_last_of('.')) + "_gnu.plt";
    out_gnu.open(filename_gnu);
    out_arrow.open(arrow_name);
    out_gnu << "rgb(r,g,b) = 65536 * int(r) + 256 * int(g) + int(b)" << endl;

    out_gnu << "plot '/Users/AlinaArslanova/untitled1/cmake-build-debug/" + filename +
               "' using 1:2:(rgb($3,$4,$5))  notitle with points lc rgb variable, ";
    out_gnu
            << " '/Users/AlinaArslanova/untitled1/cmake-build-debug/"+arrow_name+"' using 1:2:3:4 with vectors head filled  lw 2  lc rgb \"red\"";
    out.open(filename);
    //log("printing clusters to " + filename);


    int a, b, c;
    if (!out.is_open()) {
        cout << "Errors in opening" << endl;
    } else {

        for (int i = 0; i < (int) clusters.size(); i++) {
            if (clusters[i].points.size() > 10) {

                Cluster g = clusters[i];
                Point p=g.find_mass_centre();
                vector<double> values=g.find_vectors();
                out_arrow << p.x << " " << p.y<< " "<<values[0] << " "<<values[1]<< endl;
                out_arrow << p.x << " " << p.y<< " "<<values[2] << " "<<values[3]<< endl;

            }
        }

        for (int i = 0; i < (int) clusters.size(); i++) {

            a = rand() % 257;
            b = rand() % 257;
            c = rand() % 257;
            Cluster g = clusters[i];
            for (int j = 0; j < (int) g.points.size(); j++) {

                out << g.points[j].x << " " << g.points[j].y << " " << a << " " << b << " " << c << " " << endl;
            }


        }


    }
    out.close();
    out_arrow.close();
    out_gnu.close();

}