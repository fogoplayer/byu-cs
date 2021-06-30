#ifndef SNAP_H_
#define SNAP_H_
#include <string>
#include <iostream>
#include <sstream>

class Snap
{
private:
    int studentID;
    std::string studentName;
    std::string studentAddress;
    int studentPhone;

public:
    Snap(int studentID = 0, std::string studentName = "No Name Provided", std::string studentAddress = "No Address Provided", int studentPhone = 0)
    {
        this->studentID = studentID;
        this->studentName = studentName;
        this->studentAddress = studentAddress;
        this->studentPhone = studentPhone;
    }

    ~Snap()
    {
        return;
    }

    std::string to_string()
    {
        std::ostringstream objectStream;
        objectStream << "ID: " << studentID << "\n";
        objectStream << "Name: " << studentName << "\n";
        objectStream << "Address: " << studentAddress << "\n";
        objectStream << "Phone: " << studentPhone << "\n";

        return objectStream.str();
    }

    friend std::ostream &operator<<(std::ostream &os, Snap &snapInstance)
    {
        os << snapInstance.to_string();
    }
};
#endif