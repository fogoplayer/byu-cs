#ifndef COURSEINTERFACE_H_
#define COURSEINTERFACE_H_

#include <string>

class CourseInterface
{
protected:
    std::string courseName;

public:
    CourseInterface(std::string courseName) : courseName(courseName) {}
    ~CourseInterface() {}

    virtual std::string getCourseName()
    {
        return courseName;
    };
};

#endif