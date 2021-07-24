#ifndef STATION_H_
#define STATION_H_

#include "Stack.h"
#include "Queue.h"
#include "Vector.h"

template <typename T>
class Station
{
private:
    Stack<T> stack;
    Queue<T> queue;
    Vector<T> vector;
    T *turntable;

public:
    Station() : stack(Stack<T>()), queue(Queue<T>()), vector(Vector<T>()) {}
    ~Station()
    {
        delete turntable;
    }

    /**
     * Put a car onto the station turntable
     * @param newCar the new car to add to the turntable
     * @return "OK" if successful, error text if not
     */
    std::string addCar(const T &newCar)
    {
        turntable = new T(newCar);
        return "OK";
    }

    /**
     * Put a car into the stack
     * @return "OK" if successful, error text if not
     */
    std::string addStack()
    {
        try
        {
            stack.push(*turntable);
            turntable = nullptr;
            return "OK";
        }
        catch (std::string e)
        {
            return e;
        }
    }

    /**
     * Put a car into the queue
     * @return "OK" if successful, error text if not
     */
    std::string addQueue()
    {
        try
        {
            queue.push(*turntable);
            turntable = nullptr;
            return "OK";
        }
        catch (std::string e)
        {
            return e;
        }
    }

    /**
     * Put a car on the turntable into the vector
     * @return "OK" if successful, error text if not
     */
    std::string removeCar()
    {
        try
        {
            vector.push(*turntable);
            turntable = nullptr;
            return "OK";
        }
        catch (std::string e)
        {
            return e;
        }
    }

    /**
     * Put a car onto the turntable from the queue
     * @return "OK" if successful, error text if not
     */
    std::string removeQueue()
    {
        try
        {
            *turntable = queue.front();
            queue.pop();
            return "OK";
        }
        catch (std::string e)
        {
            return e;
        }
    }

    /**
     * Put a car onto the turntable from the stack
     * @return "OK" if successful, error text if not
     */
    std::string removeStack()
    {
        try
        {
            *turntable = stack.top();
            stack.pop;
            return "OK";
        }
        catch (std::string e)
        {
            return e;
        }
    }

    /**
     * Get the data from the car on the turntable
     * @return Car data if successful, error text if not
     */
    std::string topCar()
    {
        try
        {
            return *turntable.toString();
        }
        catch (string::e)
        {
            return e;
        }
    }

    /**
     * Get the data from the car on top of the stack
     * @return Car data if successful, error text if not
     */
    std::string topStack()
    {
        try
        {
            return stack.top().toString();
        }
        catch (string::e)
        {
            return e;
        }
    }

    /**
     * Get the data from the car at the front of the queue
     * @return Car data if successful, error text if not
     */
    std::string topQueue()
    {
        try
        {
            return queue.front().toString();
        }
        catch (string::e)
        {
            return e;
        }
    }

    /** 
     * Get the size of the stack
     * @return the size as a string
     */
    string sizeStack()
    {
        return stack.size();
    }
    /** 
     * Get the size of the queue
     * @return the size as a string
     */
    string sizeQueue()
    {
        return queue.size();
    }
    /** 
     * Get the size of the train
     * @return the size as a string
     */
    string sizeTrain()
    {
        return vector.size();
    }
};

#endif