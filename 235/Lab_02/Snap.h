#ifndef SNAP_H_
#define SNAP_H_
#include <string>
#include <iostream>
#include <sstream>

class Snap
{
private:
    std::string studentID;
    std::string studentName;
    std::string studentAddress;
    std::string studentPhone;

public:
    /**
     * @param studentID defaults to 0
     * @param studentName defaults to "No Name Provided"
     * @param studentAddress defaults to "No Address Provided"
     * @param studentPhone defaults to "No Phone Provided"
    **/
    Snap(std::string studentID = "0", std::string studentName = "No Name Provided", std::string studentAddress = "No Address Provided", std::string studentPhone = "No Phone Provided")
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
    std::string getStudentID() const
    {
        return this->studentID;
    }

    /**
     * @return studentName as string
    **/
    std::string getStudentName() const
    {
        return this->studentName;
    }

    /**
     * @return studentAddress as string
    **/
    std::string getStudentAddress() const
    {
        return this->studentAddress;
    }

    /**
     * @return studentPhone as string
    **/
    std::string getStudentPhone() const
    {
        return this->studentPhone;
    }

    /**
     * @return a 4-line string with the contents of all private data members
    **/
    std::string to_string()
    {
        std::ostringstream objectStream;
        objectStream << "snap(" << studentID;
        objectStream << "," << studentName;
        objectStream << "," << studentAddress;
        objectStream << "," << studentPhone << ")";

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