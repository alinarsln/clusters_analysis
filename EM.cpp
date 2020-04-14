//
// Created by AlinaArslanova on 30.03.2020.
//

#include "EM.h"



vector<vector<double>> EM::matrix_composition(vector<vector<double>> a ,vector<vector<double>> b)
{
    vector<vector<double>> c(a.size());
    for(int i=0;i<a.size();i++)
        for(int j=0;j<b[0].size();j++)
            c[i].push_back(0);
    for(int i=0;i<a.size();i++)
    {
        for(int j=0;j<b[0].size();j++)
        {
            for(int k=0;k<a[i].size();k++)
            {
                c[i][j]=c[i][j]+a[i][k]*b[k][j];
            }

        }
    }
    return c;
}
vector<vector<double>> EM::matrix_transporation(vector<vector<double>>a)
{
    vector<vector<double>> c(a[0].size());
    for(int i=0;i<a[0].size();i++)
        for(int j=0;j<a.size();j++)
            c[i].push_back(0);
    for(int i=0;i<a[0].size();i++)
    {
        for(int j=0;j<a.size();j++)
        {
            c[i][j]=a[j][i];
        }
    }
    return c;
}


double EM:: determinat(vector<vector<double>> a)
{
    double det = 1;
    int n=a.size();
    double e=0.01;
    for (int i=0; i<n; ++i) {
        int k = i;
        for (int j=i+1; j<n; ++j)
            if (fabs (a[j][i]) > fabs (a[k][i]))
                k = j;
        if (fabs (a[k][i]) < e) {
            det = 0;
            break;
        }
        swap (a[i], a[k]);
        if (i != k)
            det = -det;
        det *= a[i][i];
        for (int j=i+1; j<n; ++j)
            a[i][j] /= a[i][i];
        for (int j=0; j<n; ++j)
            if (j != i && fabs (a[j][i]) > e)
                for (int k=i+1; k<n; ++k)
                    a[j][k] -= a[i][k] * a[j][i];
    }
    return det;
}
vector<vector<double>> EM::matrix_reversal(vector<vector<double>>a) {
    vector<vector<double>> c(a.size());
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a.size(); j++) {
            c[i].push_back(0);
            if (i == j) c[i][j] = 1;
        }
    if(determinat(a)!=0) {

        vector<vector<double>> c(a.size());
        for (int i = 0; i < a.size(); i++)
            for (int j = 0; j < a.size(); j++) {
                c[i].push_back(0);
                if (i == j) c[i][j] = 1;
            }


        for (int i = 0; i < a.size(); i++) {
            double tmp0 = a[i][i];
            for (int j = 0; j < a[i].size(); j++) {
                if (a[i][j] == 0 && i == j) {
                    for (int k = i; k < a.size(); k++) {
                        if (a[k][i] != 0) {
                            for (int p = 0; p < a.size(); p++) {
                                double tmp = a[k][p];
                                a[k][p] = a[i][p];
                                a[i][p] = tmp;
                                double tmp2 = c[k][p];
                                c[k][p] = c[i][p];
                                c[i][p] = tmp2;
                            }
                            break;

                        }
                    }
                } else {
                    a[i][j] = a[i][j] / tmp0;
                    c[i][j] = c[i][j] / tmp0;
                }
            }
            for (int k = 0; k < a.size(); k++) {
                double tmp = a[k][i];
                for (int j = 0; j < a.size(); j++) {
                    if (k != i) {
                        a[k][j] = a[k][j] - a[i][j] * tmp;
                        c[k][j] = c[k][j] - c[i][j] * tmp;
                    }

                }

            }
        }

    }
    return c;

}


vector<vector<double>> matrix_addition(vector<vector<double>> a,vector<vector<double>> b)
{
    vector<vector<double>> c(a.size());
    for(int i=0;i<a.size();i++)
        for(int j=0;j<a[i].size();j++)
        {
            c[i].push_back(a[i][j]+b[i][j]);
        }
    return c;
}


void EM:: em_alg(int cl) {
    int dim=2;
    double e=0.1;
    int Q=0;
    vector<vector<double>> Y(points_nmb);//xi
    for(int i=0;i<points_nmb;i++)//point_nmb*dim
    {
        Y[i].push_back(f.all_points[i].x);
        Y[i].push_back(f.all_points[i].y);
    }


    vector<vector<double>> C(dim);//mathematical expectation

    for(int i=0;i<cl;i++) {
        for (int i = 0; i < 2; i++) {
            C[i].resize(cl);

            for (int j = 0; j < cl; j++) {
                C[i][j] = (double)(rand() % 1000)/1000;

            }
        }
    }


    vector<vector<vector<double>>> R(cl);//sigma covariation matrix

    for(int i=0;i<cl;i++) {
        R[i].push_back({1,0});
        R[i].push_back({0,1});

    }


    vector<double> W(cl);

    for(int i=0;i<cl;i++) {
        W[i] = (double) 1 / cl;
    }


    vector<vector<long double>>X(points_nmb, vector<long double>(cl, 0));



    long double llh=0,llh2=e+2;
    long double sumpi=0;

    //start cycle
    while(fabs(llh2-llh)>=e and Q<50)
    {
        vector <vector <double> > Ctmp (dim, vector<double>(cl, 0));

        vector <double> Wtmp(cl, 0);

        Q++;
        llh=llh2;
        vector<vector<vector<double>>> Rtmp(cl);

        for(int i=0;i<cl;i++) {
            Rtmp[i].push_back({0,0});
            Rtmp[i].push_back({0,0});

        }

        llh2=0;
        for(int i=0;i<points_nmb;i++)
        {

            sumpi=0;
            for(int j=0;j<cl;j++)
            {
                vector<vector<double>> l(dim);

                for(int k=0;k<dim;k++)
                {
                    l[k].push_back(Y[i][k]-C[k][j]);

                }
                double sigma=matrix_composition(matrix_composition(matrix_transporation(l),matrix_reversal(R[j])),l)[0][0];//scalar product- mahalanobis distination
                X[i][j] = (long double)W[j] * expl((long double)-sigma/2)/sqrt(2*PI)/sqrt(determinat(R[j]));
                sumpi+=X[i][j];//found p(x)

            }
            for(int j=0;j<cl;j++) {
                X[i][j]/= sumpi;
                Wtmp[j]+=X[i][j];
                Ctmp[0][j]+= Y[i][0] * X[i][j];
                Ctmp[1][j]+=Y[i][1] * X[i][j];
            }

            llh2=llh2+log(sumpi);

        }

        for(int j=0;j<cl;j++)
        {
            for(int k=0;k<dim;k++)
            {
                C[k][j]=Ctmp[k][j]/Wtmp[j];
            }


            for(int i=0;i<points_nmb;i++)
            {
                vector<vector<double>> l(dim);
                vector<vector<double>> r(dim);
                for(int k=0;k<dim;k++)
                {
                    l[k].push_back((Y[i][k]-C[k][j])*X[i][j]);
                    r[k].push_back((Y[i][k]-C[k][j]));
                }

                Rtmp[j][0][0]+=(Y[i][0]-C[0][j])*(Y[i][0]-C[0][j])*X[i][j];
                Rtmp[j][1][1]+=(Y[i][1]-C[1][j])*(Y[i][1]-C[1][j])*X[i][j];
            }
            for (int i = 0; i < cl; i++) {
                W[i] = Wtmp[i]/points_nmb;
            }
            R[j][0][0] = Rtmp[j][0][0]/Wtmp[j];
            R[j][1][1] = Rtmp[j][1][1]/Wtmp[j];

        }
        make_clusters(X,cl);


    }



}
void EM::make_clusters(  vector<vector<long double>>X,int cl)
{
    clusters.clear();
    for(int i=0;i<cl;i++) {
        Cluster cluster;
        clusters.push_back(cluster);
    }

    for(int i=0;i<points_nmb;i++)
    {
        int max=0;
        int cl_i=0;
        for(int j=0;j<cl;j++)
        {
            if(X[i][j]>=max)
            {
                max=X[i][j];
                cl_i=j;

            }
        }
        clusters[cl_i].points.push_back(f.all_points[i]);
    }
    clusters_for_film.push_back(clusters);

}
void EM::make_film( ofstream &out,string filename)
{
    ofstream out_gnu;

    string filename_gnu = filename.substr(0, filename.find_last_of('.')) + "_gnu.plt";
    out_gnu.open(filename_gnu);


    out_gnu<<"set terminal gif  animate delay 100"<<endl;
    out_gnu<<"set output 'try.gif'"<<endl;
    out_gnu<<"do for [i=0:"<<clusters_for_film.size()-1<<"] {"<<endl;
    out_gnu<<"rgb(r,g,b) = 65536 * int(r) + 256 * int(g) + int(b)"<<endl;
    out_gnu<<"plot '/Users/AlinaArslanova/untitled1/cmake-build-debug/" + filename +
        "' index i   using 1:2:(rgb($3,$4,$5))   title \"EM algorythm k="+to_string(cl)+"\" with points lc rgb variable "<<endl<<"}";
    out.open(filename);
    int a, b, c;
    vector<vector<int>> colors;
    for(int i=0;i<cl;i++)
    {
        a = rand() % 257;
        b = rand() % 257;
        c = rand() % 257;
        colors.push_back({a,b,c});
    }

    if (!out.is_open()) {
        cout << "Errors in opening" << endl;
    } else {

        for(int k=0;k<clusters_for_film.size();k++) {
            for (int i = 0; i < (int) clusters_for_film[k].size(); i++) {


                Cluster g = clusters_for_film[k][i];
                for (int j = 0; j < (int) g.points.size(); j++) {

                    out << g.points[j].x << " " << g.points[j].y << " " << colors[i][0] << " " << colors[i][1] << " " << colors[i][2] << " " << endl;
                }


            }
            out<<endl<<endl;
        }


    }
    out.close();

    out_gnu.close();

}


void EM::print_clusters(ofstream &out,string filename) {
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


