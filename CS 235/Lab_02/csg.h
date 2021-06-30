#ifndef CSG_H_
#define CSG_H_

#include <string>
#include <iostream>
#include <sstream>

#include "courseInterface.h"

class Csg : CourseInterface
{
private:
    std::string courseName;
    int studentID;
    char studentGrade;

public:
    /**
     * @param courseName defaults to "No Name Provided"
     * @param studentID defaults to 0
     * @param studentGrade defaults to 'Z'
    **/
    Csg(std::string courseName = "No Name Provided", int studentID = 0, char studentGrade = 'Z') : CourseInterface()
    {
        this->courseName = courseName;
        this->studentID = studentID;
        this->studentGrade = studentGrade;
    }

    ~Csg() {}

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
    std::string getCourseName()
    {
        return this->courseName;
    }

    /**
     * @return a 4-line string with the contents of all private data members
    **/
    std::string to_string()
    {
        std::ostringstream objectStream;
        objectStream << "Name: " << courseName << "\n";
        objectStream << "ID: " << studentID << "\n";
        objectStream << "Grade: " << studentGrade << "\n";

        return objectStream.str();
    }

    /**
     * @return an ostream with the contents of all private data members
    **/
    friend std::ostream &operator<<(std::ostream &os, Csg &CsgInstance)
    {
        os << CsgInstance.to_string();
        return os;
    }
};
#endif