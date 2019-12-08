

#include "Field.h"

void Field::add(Group g) {
    groups.push_back(g);
    add_points(g);

}

void Field::add_points(Group g) {
    for (int i = 0; i < (int) g.points.size(); i++)
        all_points.push_back(g.points[i]);

}
