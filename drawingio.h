// File:        drawingio.h
// Author:      gctien
// Date:        2018-02-15
// Description: Contains definitions and implementations of functions for file IO
//              and drawing on PNG images

#ifndef _DRAWINGIO_H_
#define _DRAWINGIO_H_

#include <string>
#include <vector>

#include "cs221util/HSLAPixel.h"
#include "cs221util/PNG.h"
#include "point.h"

using namespace cs221util;
using namespace std;

// draws a line connecting p1 and p2
// note that points are expected to be in image coordinates (e.g. top-left origin)
// pixel is used only to contain colour information
void drawLine(PNG& im, HSLAPixel pixel, Point p1, Point p2)
{
  HSLAPixel* px;

  // cases: vertical line, horizontal line, slope > 1, slope < 1
  // case 1: vertical line
  if (p1.x == p2.x)
  {
    unsigned int y1, y2;
    if (p1.y > p2.y)
    {
      y1 = (unsigned int) p2.y;
      y2 = (unsigned int) p1.y;
    }
    else
    {
      y1 = (unsigned int) p1.y;
      y2 = (unsigned int) p2.y;
    }
    for (unsigned int yc = y1; yc < y2; yc++)
    {
      px = im.getPixel((unsigned int) p1.x, yc);
      *px = pixel;
    }
  }
  // case 2: horizontal line
  else if (p1.y == p2.y)
  {
    unsigned int x1, x2;
    if (p1.x > p2.x)
    {
      x1 = (unsigned int)p2.x;
      x2 = (unsigned int)p1.x;
    }
    else
    {
      x1 = (unsigned int)p1.x;
      x2 = (unsigned int)p2.x;
    }
    for (unsigned int xc = x1; xc < x2; xc++)
    {
      px = im.getPixel(xc, (unsigned int) p1.y);
      *px = pixel;
    }
  }
  else
  {
    double slope = (p2.y - p1.y) / (p2.x - p1.x);
    double icept = p1.y - (slope * p1.x);
    // case 3: shallow slope
    // iterate over x-coordinate
    if (-1 <= slope && slope <= 1)
    {
      Point pleft, pright;
      if (p1.x < p2.x)
      {
        pleft = p1;
        pright = p2;
      }
      else
      {
        pleft = p2;
        pright = p1;
      }
      for (double xc = pleft.x; xc <= pright.x; xc++)
      {
        // calculate the y-coordinate
        double yc = (slope * xc) + icept;
        px = im.getPixel((unsigned int) xc, (unsigned int) yc);
        *px = pixel;
      }
    }
    // case 4: steep slope
    // iterate over y-coordinate
    else
    {
      Point pbottom, ptop;
      if (p1.y < p2.y)
      {
        pbottom = p1;
        ptop = p2;
      }
      else
      {
        pbottom = p2;
        ptop = p1;
      }
      for (double yc = pbottom.y; yc <= ptop.y; yc++)
      {
        // calculate the y-coordinate
        double xc = ((double)yc - icept) / slope;
        px = im.getPixel((unsigned int) xc, (unsigned int) yc);
        *px = pixel;
      }
    }
  }
}

// draws a cross centred on p
// bar length is 9 pixels
// bar thickness is 3 pixels
// pixel is used only to contain colour information
void drawPoint(PNG& im, HSLAPixel pixel, Point p)
{
  int row, column;
  HSLAPixel* px;
  // draw horizontal bar
  for (row = (int) p.y - 1; row <= (int) p.y + 1; row++)
  {
    for (column = (int) p.x - 4; column <= (int) p.x + 4; column++)
    {
      // draw the pixel if it is within the image boundaries
      if (0 <= row && (unsigned int) row < im.height() && 0 <= column && (unsigned int) column < im.width())
      {
        px = im.getPixel(column, row);
        *px = pixel;
      }
    }
  }
  // draw vertical bar
  for (row = (int) p.y - 4; row <= (int) p.y + 4; row++)
  {
    for (column = (int) p.x - 1; column <= (int) p.x + 1; column++)
    {
      // draw the pixel if it is within the image boundaries
      if (0 <= row && (unsigned int) row < im.height() && 0 <= column && (unsigned int) column < im.width())
      {
        px = im.getPixel(column, row);
        *px = pixel;
      }
    }
  }
}

// draws points passed in as a vector
// pixel is used only to contain colour information
void drawPoints(PNG& im, HSLAPixel pixel, vector<Point> v)
{
  for (unsigned int i = 0; i < v.size(); i++)
  {
    drawPoint(im, pixel, v[i]);
  }
}

// draws a polygon and its vertices
// pixel is used only to contain colour information
// v must contain the polygon's vertices in order along the boundary
void drawPolygon(PNG& im, HSLAPixel pixel, vector<Point> v)
{
  for (unsigned int i = 0; i < v.size(); i++)
  {
    drawPoint(im, pixel, v[i]);
    drawLine(im, pixel, v[i], v[(i + 1) % v.size()]);
  }
}

// reads in a delimited file containing Point data
vector<Point> readPointsFromFile(string filename)
{
  vector<Point> v;
  string line;
  double x, y;
  ifstream infile;
  infile.open(filename);
  while (infile >> x >> y)
  {
    v.push_back(Point(x,y));
  }
  return v;
}

#endif