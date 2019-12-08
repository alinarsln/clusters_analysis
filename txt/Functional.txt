//
// Created by AlinaArslanova on 02.12.2019.
//

#include "Functional.h"


void Functional::gnunorm(double xsr, double ysr, double dispx, double dispy, int count) {
    Group group;
    group.make_group(xsr, ysr, dispx, dispy, count);
    f.add(group);

}

void Functional::gnurnd(int min, int max, int count) {

    Group group;
    for (int i = 0; i < count; i++) {
        Point p((double) (rand()) / RAND_MAX * (max - min) + min, (double) (rand()) / RAND_MAX * (max - min) + min);
        group.add(p);
    }
    f.add(group);


}

void Functional::turn(int id, double alpha) {
    Group g = f.groups[id];
    Group k;
    double tmpx, tmpy;
    for (int i = 0; i < (int) g.points.size(); i++) {
        tmpx = g.points[i].x * cos(PI * alpha / 180) - sin(PI * alpha / 180) * g.points[i].y;
        tmpy = g.points[i].x * sin(PI * alpha / 180) + cos(PI * alpha / 180) * g.points[i].y;
        k.points.push_back(Point(tmpx, tmpy));

    }
    f.add(k);

}

void Functional::move(int id, double distx, double disty) {
    Group g = f.groups[id];
    Group k;
    double tmpx, tmpy;
    for (int i = 0; i < (int) g.points.size(); i++) {
        tmpx = g.points[i].x + distx;
        tmpy = g.points[i].y + disty;
        k.points.push_back(Point(tmpx, tmpy));

    }
    f.add(k);

}

void Functional::stretch(int id, double x_stretch, double y_stretch) {
    Group g = f.groups[id];
    double tmpx, tmpy;
    for (int i = 0; i < (int) g.points.size(); i++) {
        tmpx = g.points[i].x * x_stretch;
        tmpy = g.points[i].y * y_stretch;
        g.points[i].x = tmpx;
        g.points[i].y = tmpy;
    }

}

void Functional::make_wave(double porog) {
    string str = "clusters by wave method.txt";
    search.f = f;
    search.points_nmb = (int) f.all_points.size();
    search.wave(porog);


}

void Functional::tree() {

    search.f = f;
    search.points_nmb = (int) f.all_points.size();
    search.spanning_tree();
}

void Functional::make_k(int k) {
    search.f = f;
    search.points_nmb = (int) f.all_points.size();
    search.k = k;
    search.k_mean();

}

void Functional::hierarchical(int k) {
    search.f = f;
    search.points_nmb = (int) f.all_points.size();
    string str = "clusters by hierarchical method.txt";
    search.hierarchical(k);

}

void Functional::forel(double r) {
    search.f = f;
    search.points_nmb = (int) f.all_points.size();
    string str = "clusters by forel method.txt";
    search.forel(r);


}

void Functional::dbscan(int min_point, double r) {
    search.f = f;
    search.points_nmb = (int) f.all_points.size();
    string str = "clusters by dbscan method.txt";
    search.dbscan(min_point, r);

}