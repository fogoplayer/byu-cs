#ifndef STATION_H_
#define STATION_H_

#include "Stack.h"
#include "Deque.h"
#include "Vector.h"

template <typename T>
class Station
{
private:
public:
    Station() : stack(Stack()), deque(Deque()), vector(vector()) {}
    ~Station() {}
    Stack<T> stack;
    Deque<T> deque;
    Vector<T> vector;
    T turntable;
};

#endif