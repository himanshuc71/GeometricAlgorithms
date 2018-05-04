// File:        stack.h
// Author:      gctien
// Date:        2018-02-15
// Description: Definition of a stack class, PA2

#ifndef _STACK_H_
#define _STACK_H_

#include <vector>
#include "point.h"
using std::vector;

class Stack
{
  private:
    vector<Point> st;

  public:
    // accessors

    // returns the top element of the stack
    // returns a default (0,0) point if stack is empty
    Point peek();

    // returns number of elements in the stack
    int size();

    // returns true if the stack is empty, false otherwise
    bool isEmpty();

    // mutators
    // adds an item to the top of the stack
    void push(Point p);

    // removes and returns the top element of the stack
    // returns a default (0,0) point if stack is empty
    Point pop();
};

#endif
