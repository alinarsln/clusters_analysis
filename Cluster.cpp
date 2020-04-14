

#include "Cluster.h"
#include <math.h>
void  Cluster::add(Point p) {
    points.push_back(p);
}

vector<double> Cluster::find_vectors() //this function finds eighenvectors
{
    Point c=find_mass_centre();
    vector<double> p(4);
    double tmp = 0,tmp1=0,tmp2=0;
    if((int)points.size()>10) {

        vector<vector<double>> a;
        a.resize(2);
        for (int i = 0; i < 2; i++) {
            a[i].resize(2);
            for (int j = 0; j < 2; j++) {
                tmp = 0;
                for (int k = 0; k < points.size(); k++) {
                    if (i == 0) tmp1 = points[k].x - c.x;
                    else tmp1 = points[k].y - c.y;

                    if (j == 0) tmp2 = points[k].x- c.x;
                    else tmp2 = points[k].y - c.y;
                    tmp+=tmp1*tmp2;


                }

                a[i][j] =  tmp;

            }

        }
        vector<double> values;
        values.resize(2);
        double d;
        d=(a[0][0]+a[1][1])*(a[0][0]+a[1][1]) - 4*(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
        values[0] = (a[0][0] + a[1][1] + sqrt(d)) / 2;
        values[1]= (a[0][0] + a[1][1] - sqrt(d)) / 2;


        for (int i = 0; i < 2; i++) {
            p[2*i] = a[0][1]/(values[i] - a[0][0]);
            p[2*i+1] = 1/sqrt(p[2*i]*p[2*i] + 1)*sqrt(2*sqrt(values[i]));
            p[2*i] *= p[2*i+1];
        }





        return p;
    }
    else return p;
}
Point Cluster::find_mass_centre()// this function finds mass centre of the cluster
{
    double sx=0,sy=0;
    for(int i=0;i<(int)points.size();i++)
    {
        sx+=points[i].x;
        sy+=points[i].y;
    }
    sx=sx/(int)points.size();
    sy=sy/(int)points.size();
    Point p(sx,sy);
    return p;
}

