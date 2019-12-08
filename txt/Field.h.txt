#include <vector>
#include "Point.h"
#include "Cluster.h"
#include "Group.h"

#ifndef UNTITLED1_FIELD_H
#define UNTITLED1_FIELD_H


class Field {
public:
    vector<Group> groups;

    void add(Group g);

    vector<Point> all_points;

    void add_points(Group g);


};


#endif //UNTITLED1_FIELD_H
