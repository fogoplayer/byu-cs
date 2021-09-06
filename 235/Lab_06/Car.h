#ifndef CAR_H_
#define CAR_H_

#include <sstream>
#include <iostream>

struct Car
{
    unsigned int id;
    Car(unsigned int data = 0) : id(data) {}
    ~Car() {}

    bool operator==(const Car car) { return this->id == car.id; }
    bool operator!=(const Car car) { return this->id != car.id; }

    /** Return the Car as a string */
    std::string toString() const
    {
        std::stringstream out;
        out << id;
        return out.str();
    } // end toString()

    /** Make insertion operator friend for a Car */
    friend std::ostream &operator<<(std::ostream &os, const Car &c)
    {
        os << c.toString();
        return os;
    } // end operator<<
};

#endif