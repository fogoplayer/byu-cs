#ifndef CDH_H_
#define CDH_H_

#include <string>
#include <iostream>
#include <sstream>

#include "courseInterface.h"

class Cdh : public CourseInterface
{
private:
    std::string day;
    std::string time;

public:
    /**
     * @param courseName defaults to "No Name Provided"
     * @param day defaults to "No Day Provided"
     * @param time defaults to "No Time Provided"
    **/
    Cdh(std::string courseName = "No Name Provided", std::string day = "No Day Provided", std::string time = "No Time Provided") : CourseInterface(courseName), day(day), time(time) {}

    ~Cdh() {}

    /**
     * @return day as string
    **/
    std::string getCourseDay()
    {
        return this->day;
    }

    /**
     * @return time as string
    **/
    std::string getCourseTime()
    {
        return this->time;
    }

    /**
     * @return a 3-line string with the contents of all private data members
    **/
    std::string to_string()
    {
        std::ostringstream objectStream;
        objectStream << "Name: " << courseName << "\n";
        objectStream << "Day: " << day << "\n";
        objectStream << "Time: " << time << "\n";

        return objectStream.str();
    }

    /**
     * @return an ostream with the contents of all private data members
    **/
    friend std::ostream &operator<<(std::ostream &os, Cdh &CdhInstance)
    {
        os << CdhInstance.to_string();
        return os;
    }
};

#endif