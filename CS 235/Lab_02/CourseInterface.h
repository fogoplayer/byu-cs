#ifndef COURSEINTERFACE_H_
#define COURSEINTERFACE_H_

#include <string>

class CourseInterface
{
protected:
    std::string courseName;

public:
    /**
     * @param courseName
    **/
    CourseInterface(std::string courseName) : courseName(courseName) {}
    ~CourseInterface() {}

    /**
     * @return courseName as a string
    **/
    std::string getCourseName()
    {
        return courseName;
    };

    // Require a to_string
    virtual std::string to_string() = 0;
};

#endif