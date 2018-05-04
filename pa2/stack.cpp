#include <iostream>
#include "point.h"
#include "stack.h"
#include <vector>

using std::vector;


// returns the top element of the stack
// returns a default (0,0) point if stack is empty
Point Stack::peek(){
    if(isEmpty()){
        return Point();
    }
    else
        return st.back();
}

// returns number of elements in the stack
int Stack::size(){
    return st.size();
}

// returns true if the stack is empty, false otherwise
bool Stack::isEmpty(){
    return st.empty();
}

// adds an item to the top of the stack
void Stack::push(Point p){
    st.push_back(p);
}

// removes and returns the top element of the stack
// returns a default (0,0) point if stack is empty
Point Stack::pop(){
    if(isEmpty())
        return Point();
    else{
        Point point=peek();
        st.pop_back();
        return point;
    }
}

