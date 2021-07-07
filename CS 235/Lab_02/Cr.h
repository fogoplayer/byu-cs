#ifndef CR_H_
#define CR_H_

#include "CourseInterface.h"

class Cr : public CourseInterface
{
private:
    std::string room;

public:
    /**
     * @param courseName defaults to "No Name Provided"
     * @param room defaults to "No Room Provided"
    **/
    Cr(std::string courseName = "No Name Provided", std::string room = "No Room provided") : CourseInterface(courseName), room(room){};
    ~Cr(){};

    /**
     * @return the room number as a string
    **/
    std::string getRoom()
    {
        return room;
    }

    /**
     * @return a 4-line string with the contents of all private data members
    **/
    std::string to_string()
    {
        std::ostringstream objectStream;
        objectStream << "Name: " << courseName << "\n";
        objectStream << "Room: " << room << "\n";

        return objectStream.str();
    }

    /**
     * @return an ostream with the contents of all private data members
    **/
    friend std::ostream &operator<<(std::ostream &os, Cr &CrInstance)
    {
        os << CrInstance.to_string();
        return os;
    }
};

#endif