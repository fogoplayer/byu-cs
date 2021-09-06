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
    Station() : stack(Stack<T>()), queue(Queue<T>()), vector(Vector<T>()), turntable(nullptr) {}
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
        delete turntable;
        turntable = new T(newCar);
        return "OK";
    }

    /**
     * Put a car into the stack
     * @return "OK" if successful, error text if not
     */
    std::string addStack();

    /**
     * Put a car into the queue
     * @return "OK" if successful, error text if not
     */
    std::string addQueue();

    /**
     * Put a car on the turntable into the vector
     * @return "OK" if successful, error text if not
     */
    std::string removeCar();

    /**
     * Put a car onto the turntable from the queue
     * @return "OK" if successful, error text if not
     */
    std::string removeQueue();

    /**
     * Put a car onto the turntable from the stack
     * @return "OK" if successful, error text if not
     */
    std::string removeStack();

    /**
     * Get the data from the car on the turntable
     * @return Car data if successful, error text if not
     */
    std::string topCar();

    /**
     * Get the data from the car on top of the stack
     * @return Car data if successful, error text if not
     */
    std::string topStack();

    /**
     * Get the data from the car at the front of the queue
     * @return Car data if successful, error text if not
     */
    std::string topQueue();

    /** 
     * Get the size of the stack
     * @return the size as a std::string
     */
    std::string sizeStack()
    {
        std::ostringstream os;
        os << stack.size();
        return os.str();
    }

    /** 
     * Get the size of the queue
     * @return the size as a std::string
     */
    std::string sizeQueue()
    {
        std::ostringstream os;
        os << queue.size();
        return os.str();
    }

    /** 
     * Get the size of the train
     * @return the size as a std::string
     */
    std::string sizeTrain()
    {
        std::ostringstream os;
        os << vector.size();
        return os.str();
    }

    /**
     * Get the stack as a string
     * @return the contents of the stack as a string
     */
    std::string stackString()
    {
        return stack.toString();
    }

    /**
     * Get the queue as a string
     * @return the contents of the queue as a string
     */
    std::string queueString()
    {
        return queue.toString();
    }

    /**
     * Get the train as a string
     * @return the contents of the train as a string
     */
    std::string trainString()
    {
        return vector.toString();
    }

    /**
     * Search for a provided value in the queue
     * @param node data the data to search for
     * @return the index as a string or "false"
     */
    std::string queueFind(T &node)
    {
        return queue.find(node);
    }

    /**
     * Search for a provided value in the stack
     * @param node data the data to search for
     * @return the index as a string or "false"
     */
    std::string stackFind(T &node)
    {
        return stack.find(node);
    }

    /**
     * Search for a provided value in the train
     * @param node data the data to search for
     * @return the index as a string or "false"
     */
    std::string trainFind(T &node)
    {
        return vector.find(node);
    }
};

template <typename T>
std::string Station<T>::addStack()
{
    try
    {
        if (turntable == nullptr)
        {
            std::string errMsg = "Turntable empty!";
            throw errMsg;
        }
        stack.push(*turntable);
        delete turntable;
        turntable = nullptr;
        return "OK";
    }
    catch (std::string e)
    {
        return e;
    }
}

template <typename T>
std::string Station<T>::addQueue()
{
    try
    {
        if (turntable == nullptr)
        {
            std::string errMsg = "Turntable empty!";
            throw errMsg;
        }
        queue.push(*turntable);
        delete turntable;
        turntable = nullptr;
        return "OK";
    }
    catch (std::string e)
    {
        return e;
    }
}

template <typename T>
std::string Station<T>::removeCar()
{
    try
    {
        if (turntable == nullptr)
        {
            std::string errMsg = "Turntable empty!";
            throw errMsg;
        }
        vector.push_back(*turntable);
        delete turntable;
        turntable = nullptr;
        return "OK";
    }
    catch (std::string e)
    {
        return e;
    }
}

template <typename T>
std::string Station<T>::removeQueue()
{
    try
    {
        delete turntable;
        turntable = new T(queue.front());
        queue.pop();
        return "OK";
    }
    catch (std::string e)
    {
        return "Queue " + e;
    }
}

template <typename T>
std::string Station<T>::removeStack()
{
    try
    {
        delete turntable;
        turntable = new T(stack.top());
        stack.pop();
        return "OK";
    }
    catch (std::string e)
    {
        return "Stack " + e;
    }
}

template <typename T>
std::string Station<T>::topCar()
{
    try
    {
        return turntable->toString();
    }
    catch (std::string e)
    {
        return e;
    }
}

template <typename T>
std::string Station<T>::topStack()
{
    try
    {
        return stack.top().toString();
    }
    catch (std::string e)
    {
        return e;
    }
}

template <typename T>
std::string Station<T>::topQueue()
{
    try
    {
        return queue.front().toString();
    }
    catch (std::string e)
    {
        return e;
    }
}

#endif