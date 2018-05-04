#include "convexhull.h"

using namespace std;


// uses a sorting algorithm of your choice (must be fully implemented by you)
// to sort the points in v to satisfy the following criteria:
// 1. v[0] must contain the point with the smallest y-coordinate.
//      If multiple points have the same smallest y-coordinate, v[0]
//      must contain the one among those with the smallest x-coordinate.
// 2. The remaining indices i contain the points, sorted in increasing order
//      by the angle that the point forms with v[0] and the x-axis. THat is,
// 	one of the legs of the angle is represened by the line through v[0] and
//	v[i], and the other is the x-axis.
void sortByAngle(vector <Point> &v) {
    int yMin = v[0].y;
    int minCoord = 0;
    for (unsigned i = 0; i < v.size(); i++) {
        if (v[i].y < yMin || (v[i].y == yMin && v[i].x < v[minCoord].x)) {
            yMin = v[i].y;
            minCoord = i;
        }
    }
    // point with smallest y-coordinate stored at v[0]
    swap(v[0],v[minCoord]);

    //sorting by angles
    Point p = v[0];
    for (unsigned j = 1; j < v.size(); j++) {
        float scos = (v[j].x - p.x) / distance(p, v[j]);
        int smallest = j;
        for (unsigned i = j + 1; i < v.size(); i++) {
            float cos = (v[i].x - p.x) / distance(p, v[i]);
            if (cos >= scos) {
                if (cos == scos && distance(p, v[j]) < distance(p, v[i])) {

                } else {
                    smallest = i;
                    scos = cos;
                }
            }
        }
        swap(v[j], v[smallest]);
    }
}


// determines whether a path from p1 to p2 to p3 describes a counterclockwise turn
bool ccw(Point p1, Point p2, Point p3) {
    return ((p2.x - p1.x) * (p3.y - p1.y)
            - (p2.y - p1.y) * (p3.x - p1.x) > 0);

}

// returns a vector of points representing the convex hull of v
// if c is the vector representing the convex hull, then c[k], c[k+1]
// is an edge in the convex hull, for all k in 0 to n-1, where n is the
// number of points in the hull. c[n-1],c[0] is also an edge in the hull.
// The returned vector should be a subset of v
// Input: v - a vector of points in arbitrary order
vector <Point> getConvexHull(vector <Point> &v) {
    if (v.size() < 3) {
        vector <Point> p = {};
        return p;
    }

    sortByAngle(v);
    vector <Point> ret;
    Stack tempS;
    tempS.push(v[0]);
    tempS.push(v[1]);
    tempS.push(v[2]);

    for (unsigned i = 3; i < v.size(); i++) {
        while (!ccw(stackNextToTop(tempS), tempS.peek(), v[i])) {
            tempS.pop();
        }
        tempS.push(v[i]);
    }

    while (!tempS.isEmpty()) {
        ret.push_back(tempS.pop());
    }

    sortByAngle(ret);

    return ret;
}

// returns the next to top element from the stack
Point stackNextToTop(Stack &s) {
    Point top = s.pop();
    Point ret = s.peek();
    s.push(top);
    return ret;
}

// returns the distance between two points
float distance(Point a, Point b) {
    float dist = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    return dist;
}

// swaps two points
void swap(Point &a, Point &b) {
    Point temp = a;
    a = b;
    b = temp;
}