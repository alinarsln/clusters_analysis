//
// Created by AlinaArslanova on 30.03.2020.
//

#include "Spanning_tree.h"
void Spanning_tree::distance_matrix() {
    a.clear();
    for (int i = 0; i < points_nmb; i++) {
        vector<double> dist_for_point;
        for (int j = 0; j < points_nmb; j++) {
            dist_for_point.push_back(f.all_points[i].dist( f.all_points[j]));
        }
        a.push_back(dist_for_point);

    }
}

void Spanning_tree::spanning_tree() {
    distance_matrix();
    vector<bool> used(points_nmb, false);
    vector<double> min_e(points_nmb, a[0][1]);
    vector<int> sel_e(points_nmb, -1);
    for (int i = 0; i < points_nmb; i++) {
        int v = -1;
        for (int j = 0; j < points_nmb; j++)
            if ((!used[j]) && (v == -1 || (v != -1 && min_e[j] <= min_e[v])))
                v = j;

        used[v] = true;
        if (sel_e[v] != -1) {
            tree_edges.push_back(make_pair(f.all_points[v], f.all_points[sel_e[v]]));
            tree_length.push_back(f.all_points[v].dist( f.all_points[sel_e[v]]));

        }
        for (int to = 0; to < points_nmb; ++to)
            if (a[v][to] < min_e[to]) {
                min_e[to] = a[v][to];
                sel_e[to] = v;
            }
    }
}
void Spanning_tree::print_tree(ofstream &out,string filename) {
    ofstream out_gnu;
    string filename_gnu = filename.substr(0, filename.find_last_of('.')) + "_gnu.plt";
    out_gnu.open(filename_gnu);
    out_gnu << "plot '/Users/AlinaArslanova/untitled1/cmake-build-debug/" << filename
            << "'  u 1:2 with lines lc rgb \"black\" lw 2 notitle" << endl;
    out.open(filename);

    for (int i = 0; i < (int) tree_edges.size(); i++) {

        out << tree_edges[i].first.x << " " << tree_edges[i].first.y << endl;
        out << tree_edges[i].second.x << " " << tree_edges[i].second.y << endl;
        out << endl;

    }
    out.close();
    out_gnu.close();

}
/*else if (a == "print_tree") {
            string filename;
            int n;
            *in >> filename >> n;
            ofstream out;
            ofstream out_gnu;
            string filename_gnu = filename.substr(0, filename.find_last_of('.')) + "_gnu.plt";
            out_gnu.open(filename_gnu);
            out_gnu << "plot '/Users/AlinaArslanova/untitled1/cmake-build-debug/" << filename
                    << "'  u 1:2 with lines lc rgb \"black\" lw 2 notitle" << endl;
            out.open(filename);
            log("printing spanning tree to " + filename);
            print_tree(out, plane.searches[n].tree_edges);
            out.close();
            out_gnu.close();
        }
        */