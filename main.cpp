#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <cmath>
#include <utility>
#include <stdio.h>

using namespace std;
#define PI 3.14159265
#define  e 0.0001

class Point {


public:
    double x, y;

    Point(double x, double y) {
        this->x = x;
        this->y = y;

    };

    double show_x() {
        return x;
    }

    double show_y() {
        return y;
    }

    friend bool operator==(const Point &p, const Point &k) {
        return (abs(p.x - k.x) < e && abs(p.y - k.y) < e);
    }

    friend bool operator!=(const Point &p, const Point &k) {
        return (abs(p.x - k.x) >= e || abs(p.y - k.y) >= e);
    }
};

class Group {
public:
    vector<Point> points;

    void add(Point p) {
        points.push_back(p);
    }

    void erase() {
        points.clear();


    }


    void make_group(double xsr, double ysr, double dispx, double dispy, int count) {


        erase();


        double sx, sy, rand1, rand2;
        srand(time(NULL));
        double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

        for (int i = 0; i < count; i++) {
            sx = 0;
            sy = 0;
            for (int j = 0; j < 1000; j++) {
                rand1 = (double) (rand()) * fraction * (2 * dispx + 1) + xsr - dispx;
                rand2 = (double) (rand()) * fraction * (2 * dispy + 1) + ysr - dispy;
                sx = sx + rand1;
                sy = sy + rand2;

                //sx += -1+(rand() %10000)*0.0002;
                // sy +=-1+ (rand() %10000)*0.0002;

            }

            sx = sx / 1000;
            sy = sy / 1000;
            Point p(sx, sy);
            //Point p(xsr + dispx * sx, ysr + dispy * sy);
            add(p);
        }


    }


};

class Cluster {
public:

    vector<Point> points;

    void add(Point p) {
        points.push_back(p);
    }
};


class Field {
public:
    vector<Group> groups;

    void add(Group g) {
        groups.push_back(g);
        add_points(g);

    }

    vector<Point> all_points;

    void add_points(Group g) {
        for (int i = 0; i < (int) g.points.size(); i++)
            all_points.push_back(g.points[i]);

    }


};

class My_Search {
public:
    Field f;
    int points_nmb;
    vector<vector<double>> a;
    int **b;
    int k;
    vector<Cluster> clusters_by_k;
    vector<Cluster> clusters_by_wave;
    vector<Cluster> clusters_hiearchichal;
    vector<Cluster> clusters_by_forel;
    vector<Cluster> clusters_by_dbscan;

    double dist(Point q, Point p) {
        double distx, disty;
        distx = q.show_x() - p.show_x();
        disty = q.show_y() - p.show_y();
        return sqrt(distx * distx + disty * disty);
    }

    void distance_matrix() {
        a.clear();
        for (int i = 0; i < points_nmb; i++) {
            vector<double> dist_for_point;
            for (int j = 0; j < points_nmb; j++) {
                dist_for_point.push_back(dist(f.all_points[i], f.all_points[j]));
            }
            a.push_back(dist_for_point);

        }
    }

    void binary_matrix(double dt) {
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

    void print_matrix() {

        ofstream gnu("distance_matrix.txt");
        for (int i = 0; i < points_nmb; i++) {
            for (int j = 0; j < points_nmb; j++) {
                gnu << a[i][j] << " ";

            }
            gnu << endl;
        }

    }

    void wave(double dt) {
        int *c = new int[points_nmb];
        binary_matrix(dt);
        for (int i = 0; i < points_nmb; i++)
            c[i] = 0;
        int newpoints_nmb = 0, s = 0, tmp;
        c[0] = 1;
        newpoints_nmb++;

        while (s < points_nmb) {//poka vse tochki ne budut v kakoi-nibud gruppe.
            for (int i = 0; i < points_nmb; i++) //idem po vsem tochkam
            {
                if (c[i] == 1) {
                    for (int j = 0; j < points_nmb; j++) {
                        if ((b[i][j] == 1) && (c[j] == 0)) {
                            c[j] = 1;
                            newpoints_nmb++;
                        }
                    }
                }
            }

            s = s + newpoints_nmb;
            Cluster cluster;
            for (int i = 0; i < points_nmb; i++)
                if (c[i] > 0) {
                    cluster.points.push_back(f.all_points[i]);
                    c[i] = -1;//pomechaem dobavlennuyu
                }//dobavili v gruppu vezde gde >0 i pometili dobavlennae -1
            clusters_by_wave.push_back(cluster);
            newpoints_nmb = 0;

            if (s < points_nmb) {
                for (int i = 0; i < points_nmb; i++) {
                    if (c[i] == 0) {//ishem pervuyu ne dobavlennuyu
                        tmp = i;
                        break;
                    }

                }
                c[tmp] = 1;
                newpoints_nmb++;// sozdali novuyu gruppu
            }

        }
    }

    void print_new(vector<Cluster> clusters, string str) {

        int a, b, c;
        ofstream gnu(str);
        for (int i = 0; i < (int) clusters.size(); i++) {
            a = rand() % 257;
            b = rand() % 257;
            c = rand() % 257;
            Cluster g = clusters[i];
            for (int j = 0; j < (int) g.points.size(); j++) {
                gnu << g.points[j].show_x() << " " << g.points[j].show_y() << " " << a << " " << b << " " << c << endl;
            }
        }

    }

    void gnuprint(vector<Cluster> clusters, string str) {

       ofstream pipe(str);

        if (pipe) {
            pipe<<"plot '-' with lines\n";
            for (int i = 0; i < 10; i++)
               pipe<< "%d\n"<< i;
            pipe<< "%s\n"<<"e";
            pipe.close();

            // ожидание нажатия клавиши
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail());
            cin.get();
        } else
            cout << "Could not open pipe" << endl;


    }

    vector<Point> centres;
    vector<Point> old_centres;
    vector<Point> new_centres;

    void make_first_centers() {

        int p;
        int min_index;
        double min_dist;
        for (int i = 0; i < k; i++) {

            centres.push_back(f.all_points[i]);

        }
        for (int i = 0; i < points_nmb; i++) {
            Point a(0, 0);
            old_centres.push_back(a);
            new_centres.push_back(a);
        }

    }

    void iteration() {
        int min_index;

        double min_dist;
        for (int i = 0; i < points_nmb; i++) {
            min_dist = dist(f.all_points[i], centres[0]);
            min_index = 0;
            for (int j = 0; j < k; j++) {
                if (dist(f.all_points[i], centres[j]) < min_dist) {
                    min_dist = dist(f.all_points[i], centres[j]);
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

    void k_mean() {
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
            clusters_by_k.push_back(cluster);
        }
    }


    void spanning_tree() {
        distance_matrix();

        ofstream fout("graph.txt");
        ofstream forgist("edge_lengths");

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
                fout << f.all_points[v].show_x() << " " << f.all_points[v].show_y() << endl;
                fout << f.all_points[sel_e[v]].show_x() << " " << f.all_points[sel_e[v]].show_y() << endl;
                fout << endl;
                forgist << dist(f.all_points[v], f.all_points[sel_e[v]]) << endl;

            }
            for (int to = 0; to < points_nmb; ++to)
                if (a[v][to] < min_e[to]) {
                    min_e[to] = a[v][to];
                    sel_e[to] = v;
                }
        }
        fout.close();
        forgist.close();
        cout << "done!";

    }

    Point mass_centre(vector<Point> points, vector<int> inside_circle) {
        double x, y;
        for (int i = 0; i < inside_circle.size(); i++) {
            x += points[inside_circle[i]].show_x();
            y += points[inside_circle[i]].show_y();

        }
        x = x / inside_circle.size();
        y = y / inside_circle.size();
        return Point(x, y);
    }

    double dist_between_two_clusters(vector<int> p, vector<int> q) {
        double min_dist = dist(f.all_points[p[0]], f.all_points[q[0]]);
        for (int i = 0; i < p.size(); i++)
            for (int j = 0; j < q.size(); j++)
                if (dist(f.all_points[p[i]], f.all_points[q[j]]) < min_dist)
                    min_dist = dist(f.all_points[p[i]], f.all_points[q[j]]);
        return min_dist;
    }

    void change_matrix(int c, int d, vector<vector<int>> clusters) {

        a.erase(a.begin() + d);
        for (int i = 0; i < a.size(); i++)
            a[i].erase(a[i].begin() + d);

        for (int i = 0; i < a.size(); i++) {
            a[c][i] = dist_between_two_clusters(clusters[c], clusters[i]);
            a[i][c] = a[c][i];

        }

    }

    void hierarchical(int k_last) {
        double min_dist;
        int point_a, point_b;
        distance_matrix();
        vector<vector<int>> clusters;//ishodnye tochki
        for (int i = 0; i < f.all_points.size(); i++) {
            vector<int> v;
            v.push_back(i);
            clusters.push_back(v);
        }//all points in own cluster

        while ((int) clusters.size() != k_last) {
            min_dist = a[0][1];
            point_a = 0;
            point_b = 1;

            for (int i = 0;
                 i < (int) a.size(); i++) {//searching for min distance between all clusters, and the name of them
                for (int j = i + 1; j < (int) a.size(); j++)
                    if (a[i][j] < min_dist) {
                        min_dist = a[i][j];
                        point_a = i;
                        point_b = j;
                    }
            }

            clusters[point_a].insert(clusters[point_a].end(), clusters[point_b].begin(),
                                     clusters[point_b].end());//make two clusters in one// sliyanie
            clusters.erase(clusters.begin() + point_b);
            change_matrix(point_a, point_b, clusters);


        }

        for (int i = 0; i < clusters.size(); i++) {
            Cluster cluster;
            for (int j = 0; j < clusters[i].size(); j++) {
                cluster.points.push_back(f.all_points[clusters[i][j]]);
            }
            clusters_hiearchichal.push_back(cluster);

        }

        cout << "done!" << endl;

    }


    void forel(double r) {
        vector<Point> all_points2;
        for (int i = 0; i < points_nmb; i++)
            all_points2.push_back(f.all_points[i]);
        vector<int> inside_circle;
        Point y0(0, 0);
        while (all_points2.size() != 0) {
            Point x0 = all_points2[rand() % all_points2.size()];

            while (x0 != y0) {
                inside_circle.clear();
                y0 = x0;//y0-current object
                for (int i = 0; i < all_points2.size(); i++)
                    if (dist(all_points2[i], x0) < r)//searching for points that are <r
                    {
                        inside_circle.push_back(i);

                    }
                x0 = mass_centre(all_points2, inside_circle);//

            }
            Cluster cluster;
            for (int i = 0; i < inside_circle.size(); i++)
                cluster.points.push_back(all_points2[inside_circle[i]]);
            for (int i = 0; i < inside_circle.size(); i++)
                all_points2.erase(all_points2.begin() + inside_circle[i] - i);
            clusters_by_forel.push_back(cluster);
        }
        cout << "done!" << endl;

    }


    vector<int> neighbors(double r, Point x0) {
        vector<int> neighbors;
        for (int i = 0; i < f.all_points.size(); i++) {
            if (dist(f.all_points[i], x0) <= r && dist(f.all_points[i], x0) >= 0) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }

    vector<int> make_unique(vector<int> points, vector<int> add_points) {
        vector<int> t;
        for (int i = 0; i < add_points.size(); i++) {
            bool u = false;
            for (int j = 0; j < points.size(); j++) {
                if (add_points[i] == points[j]) {
                    u = true;
                    break;
                }

            }
            if (u == false) {
                t.push_back(add_points[i]);
            }
        }
        for (int i = 0; i < t.size(); i++)
            points.push_back(t[i]);
        return points;
    }


    void dbscan(int min_point_nmb, double r) {
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
                if (n.size() < min_point_nmb - 1) {
                    label[i] = -1;//it's noise-separate cluster
                } else {
                    Cluster cluster;
                    c++;
                    cluster.points.push_back(f.all_points[i]);
                    label[i] = c;
                    for (int j = 0; j < n.size(); j++) {
                        if (label[n[j]] == 0) {
                            cluster.points.push_back(f.all_points[n[j]]);
                            s.clear();
                            s = neighbors(r, f.all_points[n[j]]);
                            if (s.size() >= min_point_nmb - 1) {
                                label[n[j]] = c;
                                n = make_unique(n, s);
                            } else label[n[j]] = -1;

                        }
                        if (label[n[j]] == -1) {
                            label[n[j]] = c;
                            cluster.points.push_back(f.all_points[n[j]]);
                        }

                    }
                    clusters_by_dbscan.push_back(cluster);
                }


            }


        }
        for (int i = 0; i < points_nmb; i++) {
            if (label[i] == -1) {
                Cluster cluster;
                cluster.points.push_back(f.all_points[i]);
                clusters_by_dbscan.push_back(cluster);
            }
        }

    }

};


class Functional {
public:


    Field f;
    My_Search search;

    void gnunorm(double xsr, double ysr, double dispx, double dispy, int count) {
        Group group;
        group.make_group(xsr, ysr, dispx, dispy, count);
        f.add(group);
        cout << "group is made id=" << (int) f.groups.size() - 1 << endl;
    }

    void gnurnd(int min, int max, int count) {

        Group group;
        for (int i = 0; i < count; i++) {
            Point p((double) (rand()) / RAND_MAX * (max - min) + min, (double) (rand()) / RAND_MAX * (max - min) + min);
            group.add(p);
        }
        f.add(group);
        cout << "group is made! id:" << (int) f.groups.size() - 1 << endl;

    }


    void turn(int id, double alpha) {
        Group g = f.groups[id];
        Group k;
        double tmpx, tmpy;
        for (int i = 0; i < (int) g.points.size(); i++) {
            tmpx = g.points[i].x * cos(PI * alpha / 180) - sin(PI * alpha / 180) * g.points[i].y;
            tmpy = g.points[i].x * sin(PI * alpha / 180) + cos(PI * alpha / 180) * g.points[i].y;
            k.points.push_back(Point(tmpx, tmpy));

        }
        f.add(k);
        cout << "group is made! id:" << (int) f.groups.size() - 1 << endl;
    }

    void move(int id, double distx, double disty) {
        Group g = f.groups[id];
        Group k;
        double tmpx, tmpy;
        for (int i = 0; i < (int) g.points.size(); i++) {
            tmpx = g.points[i].x + distx;
            tmpy = g.points[i].y + disty;
            k.points.push_back(Point(tmpx, tmpy));

        }
        f.add(k);
        cout << "group is made! id:" << (int) f.groups.size() - 1 << endl;

    }

    void stretch(int id, double x_stretch, double y_stretch) {
        Group g = f.groups[id];
        double tmpx, tmpy;
        for (int i = 0; i < (int) g.points.size(); i++) {
            tmpx = g.points[i].x * x_stretch;
            tmpy = g.points[i].y * y_stretch;
            g.points[i].x = tmpx;
            g.points[i].y = tmpy;
        }

    }

    void print_group(int id) {
        Group g = f.groups[id];
        ofstream gnu("gnuxy.txt");
        for (int i = 0; i < (int) g.points.size(); i++) {
            gnu << g.points[i].show_x() << " " << g.points[i].show_y() << endl;

        }
        cout << "done!" << endl;

    }

    void print_all() {

        int a, b, c;
        ofstream gnu("gnuall.txt");


        if (!gnu.is_open()) {
            cout << "Errors in opening" << endl;
        } else {

            for (int i = 0; i < (int) f.groups.size(); i++) {

                a = rand() % 257;
                b = rand() % 257;
                c = rand() % 257;
                Group g = f.groups[i];
                for (int j = 0; j < (int) g.points.size(); j++) {

                    gnu << g.points[j].show_x() << " " << g.points[j].show_y() << " " << a << " " << b << " " << c
                        << " " << endl;
                }


            }
            cout << "done!" << endl;
            gnu.close();
        }
    }


    void load_groups() {

        ifstream fin("gnuall.txt");
        double x, y;
        int a, b, c, a1 = 0, b1 = 0, c1 = 0;
        if (!fin.is_open())
            cout << "Error in opening the file gnuall.txt for loading ";
        fin >> x >> y >> a >> b >> c;
        a1 = a;
        b1 = b;
        c1 = c;
        while (!fin.eof()) {
            Group g;
            g.points.push_back(Point(x, y));
            a = a1;
            b = b1;
            c = c1;
            while (a == a1 && b == b1 && c == c1) {
                fin >> x >> y >> a1 >> b1 >> c1;
                if (a == a1 && b == b1 && c == c1 && !fin.eof()) {
                    Point p(x, y);
                    g.points.push_back(p);
                } else {
                    break;
                }

            }
            f.add(g);

        }

        fin.close();
        cout << "done!" << endl;


    }

    void load_clusters() {
        string str;
        cout << "Enter the name of the file: ";
        cin >> str;
        vector<Cluster> clusters;
        ifstream fin(str);
        double x, y;
        int a, b, c, a1, b1, c1;
        if (!fin.is_open())
            cout << "Error in opening the file  ";
        while (fin >> x && fin >> y && fin >> a && fin >> b && fin >> c) {

            Cluster g;
            a1 = a;
            b1 = b;
            c1 = c;
            while (fin >> x >> y >> a1 >> b1 >> c1) {

                if (a1 == a && b1 == b && c1 == c) {
                    Point p(x, y);
                    g.points.push_back(p);
                };
            }
            clusters.push_back(g);
        }
        if (str == "clusters by wave method.txt")
            for (int i = 0; i < clusters.size(); i++)
                search.clusters_by_wave.push_back(clusters[i]);
        else if (str == "clusters by k-mean method.txt")
            for (int i = 0; i < clusters.size(); i++)
                search.clusters_by_k.push_back(clusters[i]);
        else if (str == "clusters by hierarchical method.txt")
            for (int i = 0; i < clusters.size(); i++)
                search.clusters_hiearchichal.push_back(clusters[i]);

        fin.close();


        cout << "done!" << endl;

    }


    void gnux(int id) {
        Group group = f.groups[id];
        ofstream gnu("gnux.txt");
        for (int i = 0; i < (int) f.groups[id].points.size(); i++) {
            gnu << group.points[i].show_x() << endl;
        }
        cout << "done!" << endl;
    }

    void make_wave(double porog) {
        string str = "clusters by wave method.txt";
        search.f = f;
        search.points_nmb = (int) f.all_points.size();
        cout << "waving..." << endl;
        search.wave(porog);
        cout << "printing matrix..." << endl;
        search.print_matrix();
        cout << "printing clusters in clusters by wave method.txt" << endl;
        search.print_new(search.clusters_by_wave, str);

    }

    void tree() {

        search.f = f;
        search.points_nmb = (int) f.all_points.size();
        search.spanning_tree();
    }


    void make_k(int k) {
        search.f = f;
        search.points_nmb = (int) f.all_points.size();
        search.k = k;
        search.k_mean();
        string str = "clusters by k-mean method.txt";
        search.print_new(search.clusters_by_k, str);
    }

    void hierarchical(int k) {
        search.f = f;
        search.points_nmb = (int) f.all_points.size();
        string str = "clusters by hierarchical method.txt";
        search.hierarchical(k);
        search.print_new(search.clusters_hiearchichal, str);
    }

    void forel(double r) {
        search.f = f;
        search.points_nmb = (int) f.all_points.size();
        string str = "clusters by forel method.txt";
        search.forel(r);
        search.print_new(search.clusters_by_forel, str);

    }

    void dbscan(int min_point, double r) {
        search.f = f;
        search.points_nmb = (int) f.all_points.size();
        string str = "clusters by dbscan method.txt";
        search.dbscan(min_point, r);
        search.gnuprint(search.clusters_by_dbscan, str);

    }


};


class My_Interface {

    string a, b;
    Functional plane;
    double min, max, xsr, ysr, dispx, dispy;
    int count;
    int id;
    double porog;
    double x, y;
public:

    void command() {
        cin >> a;
        ifstream help("help.txt");
        while (a != "exit") {
            if (a == "gnurnd") {
                cout << "Enter min and max: ";
                cin >> min >> max;
                cout << "Enter the number to generate: ";
                cin >> count;
                plane.gnurnd(min, max, count);
            } else if (a == "gnux") {
                cout << "Enter the number of the group: ";
                cin >> id;
                plane.gnux(id);
            } else if (a == "gnunorm") {
                cout << "Vvedite xsr ysr dispx dispy count: ";
                cin >> xsr >> ysr >> dispx >> dispy >> count;
                plane.gnunorm(xsr, ysr, dispx, dispy, count);
            } else if (a == "print_group") {
                cout << "Enter id  ";
                cin >> id;
                plane.print_group(id);
            } else if (a == "print_all") {
                plane.print_all();
            } else if (a == "help") {
                while (!help.eof()) {
                    getline(help, b);
                    cout << b << endl;
                }
            } else if (a == "turn") {
                double alpha;
                cout << "Enter the number of the group to turn: ";
                cin >> id;
                cout << "Enter the angle in degrees: ";
                cin >> alpha;
                plane.turn(id, alpha);
            } else if (a == "kmean") {
                int k;
                cout << "Enter the number of the cluster to find: ";
                cin >> k;
                plane.make_k(k);
                cout << "done!" << endl;
            } else if (a == "wave") {
                cout << "Enter threshold value (Vvedite znachenie poroga):";
                cin >> porog;
                plane.make_wave(porog);
                cout << "wave is made" << endl;

            } else if (a == "move") {
                cout << "Enter the number of the group to move: ";
                cin >> id;

                cout << "Enter the offset value for x:";
                cin >> x;
                cout << "Enter the offset value for y:";
                cin >> y;
                plane.move(id, x, y);

                cout << "moved" << endl;

            } else if (a == "stretch") {
                cout << "Enter the number of the group to stretch: ";
                cin >> id;

                cout << "Enter the tensile value for x:";
                cin >> x;
                cout << "Enter the tensile value for y:";
                cin >> y;
                plane.stretch(id, x, y);

                cout << "stretched " << endl;
            } else if (a == "load") {
                plane.load_groups();
            } else if (a == "load_cluster") {
                plane.load_clusters();

            } else if (a == "tree") {
                plane.tree();
            } else if (a == "forel") {
                double r;
                cout << "Enter the radius of cluster: ";
                cin >> r;
                plane.forel(r);
            } else if (a == "hier") {
                int k;
                cout << "Enter the number of clusters to find: ";
                cin >> k;
                plane.hierarchical(k);
            } else if (a == "dbscan") {
                int min_point;
                cout << "Enter the minimum number of points that form a dense area: ";
                cin >> min_point;
                double r;
                cout << "Enter the radius of cluster: ";
                cin >> r;
                plane.dbscan(min_point, r);
                cout << "done!" << endl;
            } else
                cout << a << ": command not found" << endl;


            cout << "write a command:";
            cin >> a;
        }

    }


};


int main() {

    srand(time(NULL));


    Functional plane;
    cout << "write a command:";
    My_Interface anInterface;
    anInterface.command();


    return 0;
}
