#include "convexintersection.h"
#include "convexhull.h"

using namespace std;


// determines whether a point p1 is inside or outside
// of a line segment defined by sp1 and sp2
// sp1 and sp2 should be consistently provided
// from the convex hull algorithm such that the edges
// are listed in a CCW direction
// p1 belongs to the subject polygon
// sp1 and sp2 belong to the clipping polygon
bool inside(Point p1, Point sp1, Point sp2) {
    return ccw(sp1, sp2, p1);
}

// computes the point of intersection between the line segment
// defined by s1 and s2, and the infinite line defined by
// i1 and i2.
// Assume that this will only be called when the intersection exists.
Point computeIntersection(Point s1, Point s2, Point i1, Point i2) {
    // line s1s2 is denoted as a1x + b1y = c1
    double a1 = s2.y - s1.y;
    double b1 = s1.x - s2.x;
    double c1 = a1 * (s1.x) + b1 * (s1.y);

    // line i1i2 is denoted as a2x + b2y = c2
    double a2 = i2.y - i1.y;
    double b2 = i1.x - i2.x;
    double c2 = a2 * (i1.x) + b2 * (i1.y);

    double det = a1 * b2 - a2 * b1;

    double x = (b2 * c1 - b1 * c2) / det;
    double y = (a1 * c2 - a2 * c1) / det;
    return Point(x, y);
}

// returns a vector containing a sequence of points defining
// the intersection of two convex polygons poly1 and poly2
// Inputs: poly1 and poly2 - sequences of points defining the
//                           borders of convex polygons
vector <Point> getConvexIntersection(vector <Point> &poly1, vector <Point> &poly2) {
    vector <Point> outputList = poly1;
    vector <Point> clipPolygon = poly2;
    vector <Point> inputList;
    for (unsigned i = 0; i < clipPolygon.size(); i++) { // check bounds
        inputList = outputList;
        outputList.clear();
        Point S = inputList.back();
        for (unsigned j = 0; j < inputList.size(); j++) {
            if (inside(inputList[j], clipPolygon[i], clipPolygon[(i + 1) % clipPolygon.size()])) {
                if (!inside(S, clipPolygon[i], clipPolygon[(i + 1) % clipPolygon.size()])) {
                    outputList.push_back(computeIntersection(S, inputList[j], clipPolygon[i],
                                                             clipPolygon[(i + 1) % clipPolygon.size()]));
                }
                outputList.push_back(inputList[j]);
            } else if (inside(S, clipPolygon[i], clipPolygon[(i + 1) % clipPolygon.size()]))
                outputList.push_back(computeIntersection(S, inputList[j], clipPolygon[i],
                                                         clipPolygon[(i + 1) % clipPolygon.size()]));
            S = inputList[j];
        }
    }

    return outputList;
}


