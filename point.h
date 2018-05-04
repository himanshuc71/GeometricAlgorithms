// File:        point.h
// Author:      gctien
// Date:        2018-02-15
// Description: Definition of class for storing points in 2-D Euclidean plane

#ifndef _POINT_H_
#define _POINT_H_

class Point
{
  public:
    double x;
    double y;

    Point() : x(0), y(0) {}
    Point(double cx, double cy) : x(cx), y(cy) {}
};

#endif