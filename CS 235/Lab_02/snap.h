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
    /**
     * @param studentID defaults to 0
     * @param studentName defaults to "No Name Provided"
     * @param studentAddress defaults to "No Address Provided"
     * @param studentPhone defaults to 0
    **/
    Snap(int studentID = 0, std::string studentName = "No Name Provided", std::string studentAddress = "No Address Provided", int studentPhone = 0)
    {
        this->studentID = studentID;
        this->studentName = studentName;
        this->studentAddress = studentAddress;
        this->studentPhone = studentPhone;
    }

    ~Snap() {}

    /**
     * @return studentID as int
    **/
    int getStudentID()
    {
        return this->studentID;
    }

    /**
     * @return studentName as string
    **/
    std::string getStudentName()
    {
        return this->studentName;
    }

    /**
     * @return a 4-line string with the contents of all private data members
    **/
    std::string to_string()
    {
        std::ostringstream objectStream;
        objectStream << "ID: " << studentID << "\n";
        objectStream << "Name: " << studentName << "\n";
        objectStream << "Address: " << studentAddress << "\n";
        objectStream << "Phone: " << studentPhone << "\n";

        return objectStream.str();
    }

    /**
     * @return an ostream with the contents of all private data members
    **/
    friend std::ostream &operator<<(std::ostream &os, Snap &snapInstance)
    {
        os << snapInstance.to_string();
        return os;
    }
};
#endif