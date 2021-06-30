#ifndef COURSEINTERFACE_H_
#define COURSEINTERFACE_H_

#include <string>

class CourseInterface
{
protected:
    std::string courseName;

public:
    CourseInterface() {}
    ~CourseInterface() {}

    virtual std::string getCourseName() = 0;
};

#endif