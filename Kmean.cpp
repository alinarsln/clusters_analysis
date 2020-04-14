//
// Created by AlinaArslanova on 30.03.2020.
//

#include "Kmean.h"
void Kmean::make_first_centers() {

    for (int i = 0; i < k; i++) {

        centres.push_back(f.all_points[i]);

    }
    for (int i = 0; i < points_nmb; i++) {
        Point a(0, 0);
        old_centres.push_back(a);
        new_centres.push_back(a);
    }

}

void Kmean::iteration() {
    int min_index;

    double min_dist;
    for (int i = 0; i < points_nmb; i++) {
        min_dist = f.all_points[i].dist(centres[0]);
        min_index = 0;
        for (int j = 0; j < k; j++) {
            if (f.all_points[i].dist(centres[j]) < min_dist) {
                min_dist = f.all_points[i].dist(centres[j]) ;
                min_index = j;
            }

        }
        old_centres[i].x = new_centres[i].x;
        old_centres[i].y = new_centres[i].y;
        new_centres[i].x = centres[min_index].x;
        new_centres[i].y = centres[min_index].y;
    }
    double sx = 0, sy = 0;
    int count = 0;
    for (int i = 0; i < k; i++) {
        sx = 0;
        sy = 0;
        count = 0;

        for (int j = 0; j < points_nmb; j++) {
            if (new_centres[j] == centres[i]) {
                count++;
                sx = sx + f.all_points[j].x;
                sy = sy + f.all_points[j].y;
            }
        }
        if (count != 0) centres[i].x = sx / count;

        if (count != 0) centres[i].y = sy / count;


    }

}

void Kmean::k_mean() {
    clusters.clear();
    int right = 0;
    make_first_centers();
    while (right != points_nmb) {
        right = 0;
        iteration();
        for (int i = 0; i < points_nmb; i++) {
            if (old_centres[i] == new_centres[i]) right++;
            else break;
        }

    }

    for (int i = 0; i < k; i++) {
        Cluster cluster;
        for (int j = 0; j < points_nmb; j++) {
            if (new_centres[j] == centres[i]) {
                cluster.points.push_back(f.all_points[j]);
            }
        }
        clusters.push_back(cluster);
    }
}

void Kmean::print_clusters(ofstream &out,string filename) {
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