//
// Created by AlinaArslanova on 02.12.2019.
//

#include "Functional.h"



//this function generates points
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
//turns the group that we generated
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
//moves on distx and disty
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
//stretches the group
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
//uses the wave algorithm
void Functional::make_wave(double porog) {
    string str = "clusters by wave method.txt";
    wave_search.f = f;
    wave_search.points_nmb = (int) f.all_points.size();
    wave_search.wave_alg(porog);
    searches.push_back(wave_search.clusters);

}
//makes the tree
void Functional::tree() {

    span_tree_search.f = f;
    span_tree_search.points_nmb = (int) f.all_points.size();
    span_tree_search.spanning_tree();
    searches.push_back(span_tree_search.clusters);
}
//uses k_mean algorithm
void Functional::make_k(int k) {

    kmean_search.f = f;
    kmean_search.points_nmb = (int) f.all_points.size();
    kmean_search.k = k;
    kmean_search.k_mean();
    searches.push_back(kmean_search.clusters);

}
//uses hiearchical algorithm
void Functional::hierarchical(int k) {

    hierarchical_search.f = f;
    hierarchical_search.points_nmb = (int) f.all_points.size();
    string str = "clusters by hierarchical method.txt";
    hierarchical_search.hierarchical(k);
    searches.push_back(hierarchical_search.clusters);
}
//uses FOREL algorythm
void Functional::forel(double r) {
    forel_search.f = f;
    forel_search.points_nmb = (int) f.all_points.size();
    string str = "clusters by forel method.txt";
    forel_search.forel(r);
    forel_search.forel_r=r;
    searches.push_back(forel_search.clusters);

}
//uses DBSCAN algorythm with min_point that generates dense area
void Functional::dbscan(int min_point, double r) {

    dbscan_search.f = f;
    dbscan_search.points_nmb = (int) f.all_points.size();
    string str = "clusters by dbscan method.txt";
    dbscan_search.dbscan(min_point, r);
    searches.push_back(dbscan_search.clusters);

}
void Functional:: em(int cl)
{
    em_search.f = f;
    em_search.cl=cl;
    em_search.points_nmb = (int) f.all_points.size();
    string str = "clusters by EM method.txt";
    em_search.em_alg(cl);

    searches.push_back(em_search.clusters);
}
