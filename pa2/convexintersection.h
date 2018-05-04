// File:        convexintersection.h
// Author:      gctien
// Date:        2018-02-15
// Description: Definition of methods used for computing convex intersection using
//              Sutherland-Hodgman algorithm
//              https://en.wikipedia.org/wiki/Sutherland�Hodgman_algorithm

#ifndef _CONVEXINTERSECTION_H_
#define _CONVEXINTERSECTION_H_

#include <cmath>
#include <vector>
#include "point.h"

using namespace std;

// determines whether a point p1 is inside or outside
// of a line segment defined by sp1 and sp2
// sp1 and sp2 should be consistently provided
// from the convex hull algorithm such that the edges
// are listed in a CCW direction
// p1 belongs to the subject polygon
// sp1 and sp2 belong to the clipping polygon
bool inside(Point p1, Point sp1, Point sp2);

// computes the point of intersection between the line segment
// defined by s1 and s2, and the infinite line defined by
// i1 and i2.
// Assume that this will only be called when the intersection exists.
Point computeIntersection(Point s1, Point s2, Point i1, Point i2);

// returns a vector containing a sequence of points defining
// the intersection of two convex polygons poly1 and poly2
// Inputs: poly1 and poly2 - sequences of points defining the
//                           borders of convex polygons
vector<Point> getConvexIntersection(vector<Point>& poly1, vector<Point>& poly2);

// You may add some of your own useful functions here,
// BUT DO NOT MODIFY ANY OF THE FUNCTIONS ABOVE


#endif