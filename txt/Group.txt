#include "Group.h"


void Group::add(Point p) {
    points.push_back(p);
}


void Group::make_group(double xsr, double ysr, double dispx, double dispy, int count) {

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

