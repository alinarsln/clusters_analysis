//
// Created by AlinaArslanova on 30.03.2020.
//

#include "Hierarchical.h"
void Hierarchical::distance_matrix() {
    a.clear();
    for (int i = 0; i < points_nmb; i++) {
        vector<double> dist_for_point;
        for (int j = 0; j < points_nmb; j++) {
            dist_for_point.push_back(f.all_points[i].dist(f.all_points[j]));
        }
        a.push_back(dist_for_point);

    }
}
void Hierarchical::change_matrix(int c, int d,  vector<Point> all_points) {
    a.erase(a.begin() + d);
    for (int i = 0; i < (int) a.size(); i++)
        a[i].erase(a[i].begin() + d);

    for (int i = 0; i < (int) a.size(); i++) {
        if(k!=d) {
            a[c][i] = min(all_points[c].dist( all_points[i]),all_points[d].dist(all_points[i]));
            a[i][c] = a[c][i];
        }

    }
}

void Hierarchical::hierarchical(int k_last) {
    clusters.clear();
    double min_dist;
    distance_matrix();
    vector<Point> all_points;
    for (int i = 0; i < (int) f.all_points.size(); i++) {
        Cluster cluster;
        cluster.points.push_back(f.all_points[i]);
        all_points.push_back(f.all_points[i]);
        clusters.push_back(cluster);
    }//all points in own cluster
    for (int k_clusters = 0; k_clusters < all_points.size() - k_last - 1; k_clusters++){
        min_dist = a[0][1];
        int point_a = 0;
        int point_b = 1;

        for (int i = 0;
             i < (int) a.size(); i++) {//searching for min distance between all clusters, and the name of them
            for (int j = i + 1; j < (int) a.size(); j++)
                if (a[i][j] < min_dist) {
                    min_dist = a[i][j];
                    point_a = i;
                    point_b = j;
                }
        }
        // double x, y;
        clusters[point_a].points.insert(clusters[point_a].points.end(),clusters[point_b].points.begin(),clusters[point_b].points.end());
        clusters.erase(clusters.begin()+point_b);
        /*x = (all_points[point_a].x + all_points[point_b].x)/2;
         y = (all_points[point_a].y + all_points[point_b].y)/2;

         Point p(x, y);
         h_centres.push_back(p);
         denrdogramm.push_back(make_pair(all_points[point_a], p));
         denrdogramm.push_back(make_pair(all_points[point_b], p));

         //all_points[point_a] = p;
         //all_points.erase(all_points.begin() + point_b);

         */change_matrix(point_a, point_b,  all_points);

    }
}
void Hierarchical::print_clusters(ofstream &out,string filename) {
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

/*else if (a == "print_for_hierarchical") {
            string filename;
            int n;
            *in >> filename >> n;
            ofstream out;
            ofstream out_gnu;
            string filename_gnu =
                    filename.substr(0, filename.find_last_of('.')) + "_gnu.plt";//w l lc rgb 'dark-red' lw 2
            out_gnu.open(filename_gnu);
            out_gnu << "rgb(r,g,b) = 65536 * int(r) + 256 * int(g) + int(b)" << endl;
            out_gnu << "plot '/Users/AlinaArslanova/untitled1/cmake-build-debug/" << filename <<
                    "'using 1:2:(rgb($3,$4,$5)) w linespoints pt 7 ps 0.3 lw 1 lc rgb variable notitle ";
            out.open(filename);
            log("printing for hierarchical  to " + filename);
            print_clusters_for_hier(out, plane.searches[n].denrdogramm);
            out.close();
            out_gnu.close();

        }
        */