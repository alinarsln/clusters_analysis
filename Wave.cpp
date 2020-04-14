//
// Created by AlinaArslanova on 29.03.2020.
//

#include "Wave.h"

double Wave::dist(Point q, Point p) {
    double distx, disty;
    distx = q.x - p.x;
    disty = q.y - p.y;
    return sqrt(distx * distx + disty * disty);
}

void Wave::distance_matrix() {
    a.clear();
    for (int i = 0; i < points_nmb; i++) {
        vector<double> dist_for_point;
        for (int j = 0; j < points_nmb; j++) {
            dist_for_point.push_back(dist(f.all_points[i], f.all_points[j]));
        }
        a.push_back(dist_for_point);

    }
}

void Wave::binary_matrix(double dt) {
    distance_matrix();
    b = new int *[points_nmb];
    for (int i = 0; i < points_nmb; i++)
        b[i] = new int[points_nmb];
    for (int i = 0; i < points_nmb; i++)
        for (int j = i; j < points_nmb; j++) {
            if (a[i][j] <= dt) {
                b[i][j] = 1;
                b[j][i] = 1;
            } else {
                b[i][j] = 0;
                b[j][i] = 0;
            }

        }
}
void Wave::wave_alg(double dt) {
    clusters.clear();

    set<int> used;
    binary_matrix(dt);

    for (int i = 0; i < f.all_points.size();i++) {
        if (used.count(i) != 0) continue;
        Cluster cluster;
        vector<int> queue;
        queue.push_back(i);
        while (!queue.empty()) {
            int cur = queue.front();
            queue.erase(queue.begin());
            for (int j = 0; j < f.all_points.size(); j++) {
                if (b[cur][j]==1 && used.count(j) == 0) {
                    used.insert(j);
                    cluster.points.push_back(f.all_points[j]);
                    queue.push_back(j);
                }
            }
        }
        clusters.push_back(cluster);
    }

}


void Wave::print_clusters(ofstream &out,string filename) {
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