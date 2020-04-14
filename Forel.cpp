//
// Created by AlinaArslanova on 30.03.2020.
//

#include "Forel.h"
Point Forel::mass_centre(vector<Point> points, vector<int> inside_circle) {
    double x, y;
    for (int i = 0; i < (int) inside_circle.size(); i++) {
        x += points[inside_circle[i]].x;
        y += points[inside_circle[i]].y;

    }
    x = x / (int) inside_circle.size();
    y = y / (int) inside_circle.size();
    return Point(x, y);
}
void Forel::forel(double r) {
    clusters.clear();
    forel_r=r;
    vector<Point> all_points2;
    for (int i = 0; i < points_nmb; i++)
        all_points2.push_back(f.all_points[i]);
    vector<int> inside_circle;
    Point y0(0, 0);
    while ((int) all_points2.size() != 0) {
        Point x0 = all_points2[rand() % all_points2.size()];

        while (x0 != y0) {
            inside_circle.clear();
            y0 = x0;//y0-current object
            for (int i = 0; i < (int) all_points2.size(); i++)
                if ((all_points2[i].dist(x0) ) < r)//searching for points that are <r
                {
                    inside_circle.push_back(i);

                }
            x0 = mass_centre(all_points2, inside_circle);//

        }
        forel_circles.push_back(x0);
        Cluster cluster;
        for (int i = 0; i < (int) inside_circle.size(); i++)
            cluster.points.push_back(all_points2[inside_circle[i]]);
        for (int i = 0; i < (int) inside_circle.size(); i++)
            all_points2.erase(all_points2.begin() + inside_circle[i] - i);
        clusters.push_back(cluster);
    }


}

void Forel::print_clusters(ofstream &out,string filename) {
    ofstream out_gnu;
    ofstream out_arrow;
    ofstream out_forel;
    string arrow_name=filename.substr(0, filename.find_last_of('.')) + "_arrow";
    string filename_gnu = filename.substr(0, filename.find_last_of('.')) + "_gnu.plt";
    string filename_forel = filename.substr(0, filename.find_last_of('.')) + "circle_centres";
    out_gnu.open(filename_gnu);
    out_arrow.open(arrow_name);
    out_forel.open(filename_forel);
    out_gnu << "rgb(r,g,b) = 65536 * int(r) + 256 * int(g) + int(b)" << endl;

    out_gnu << "plot '/Users/AlinaArslanova/untitled1/cmake-build-debug/" + filename +
               "' using 1:2:(rgb($3,$4,$5))  notitle with points lc rgb variable," <<
            " '/Users/AlinaArslanova/untitled1/cmake-build-debug/" + filename_forel + "' with circles";

    out.open(filename);
    //log("printing clusters to " + filename);


    int a, b, c;
    if (!out.is_open()) {
        cout << "Errors in opening" << endl;
    } else {

        for (int i = 0; i < (int) clusters.size(); i++) {
            if (clusters[i].points.size() > 10) {

                Cluster g = clusters[i];
                Point p = g.find_mass_centre();
                vector<double> values = g.find_vectors();
                out_arrow << p.x << " " << p.y << " " << values[0] << " " << values[1] << endl;
                out_arrow << p.x << " " << p.y << " " << values[2] << " " << values[3] << endl;

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
        {

            for (int i = 0; i < (int) forel_circles.size(); i++) {
                Point g = forel_circles[i];
                out_forel << g.x << " " << g.y << " " << forel_r << endl;
            }


        }
        out.close();
        out_arrow.close();
        out_gnu.close();
        out_forel.close();
    }

}
