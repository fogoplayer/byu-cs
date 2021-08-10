/**
 * Zarin Loosli - 7/7/21
**/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Snap.h"
#include "Csg.h"
#include "Cdh.h"
#include "Cr.h"

using namespace std;

/*-------------------------------Function Declarations-------------------------------*/
string findStudentNameByID(int ID, const vector<Snap> &snapVec);

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char *argv[])
{
    VS_MEM_CHECK
    // Inputs -------------------------------------------------------------------------------------------------------------
    // Check number of inputs
    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }

    // Try to open input file
    cout << "Input file: " << argv[1] << endl;
    std::ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }

    // Try to open output file
    cout << "Output file: " << argv[2] << endl;
    std::ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    // Vectors
    vector<Snap> snapVec;
    vector<Csg> csgVec;
    vector<Cdh> cdhVec;
    vector<Cr> crVec;

    string currLine;

    out << "Input Strings:" << endl;
    while (getline(in, currLine))
    {
        out << currLine;

        size_t parenPosition = currLine.find("(");
        string command = currLine.substr(0, parenPosition);

        if (command == "snap") // snap(12345,Charlie Brown,Manager,555-1234)
        {
            currLine = currLine.substr(parenPosition + 1); // 12345,Charlie Brown,Manager,555-1234)

            int id;
            int commaPosition = currLine.find(',');
            istringstream arg(currLine.substr(0, commaPosition)); // 12345
            arg >> id;
            currLine = currLine.substr(commaPosition + 1); // Charlie Brown,Manager,555-1234)

            string name;
            commaPosition = currLine.find(',');
            name = currLine.substr(0, commaPosition);      // Charlie Brown
            currLine = currLine.substr(commaPosition + 1); // Manager,555-1234)

            string address;
            commaPosition = currLine.find(',');
            address = currLine.substr(0, commaPosition);   // Manager
            currLine = currLine.substr(commaPosition + 1); // 555-1234)

            string phone;
            parenPosition = currLine.find(')');
            phone = currLine.substr(0, parenPosition); // 555-1234

            Snap snap(id, name, address, phone);
            snapVec.push_back(snap);
        }

        if (command == "csg") // csg(CS101,12345,A)
        {
            currLine = currLine.substr(parenPosition + 1); // CS101,12345,A)

            string name;
            int commaPosition = currLine.find(',');
            name = currLine.substr(0, commaPosition);      // CS101
            currLine = currLine.substr(commaPosition + 1); // 12345,A)

            int studentId;
            commaPosition = currLine.find(',');
            istringstream arg(currLine.substr(0, commaPosition)); // 12345
            arg >> studentId;
            currLine = currLine.substr(commaPosition + 1); // A)

            string grade;
            parenPosition = currLine.find(')');
            grade = currLine.substr(0, parenPosition); // A

            Csg csg(name, studentId, grade);
            csgVec.push_back(csg);
        }

        if (command == "cdh") // cdh(CS101,M,9AM)
        {
            currLine = currLine.substr(parenPosition + 1); // CS101,M,9AM)

            string name;
            int commaPosition = currLine.find(',');
            name = currLine.substr(0, commaPosition);      // CS101
            currLine = currLine.substr(commaPosition + 1); // M,9AM)

            string days;
            commaPosition = currLine.find(',');
            days = currLine.substr(0, commaPosition);      // M
            currLine = currLine.substr(commaPosition + 1); // 9AM)

            string times;
            parenPosition = currLine.find(')');
            times = currLine.substr(0, parenPosition); // 9AM

            Cdh cdh(name, days, times);
            cdhVec.push_back(cdh);
        }

        if (command == "cr") // cr(CS101,1170 TMCB)
        {
            currLine = currLine.substr(parenPosition + 1); // CS101,1170 TMCB)

            string name;
            int commaPosition = currLine.find(',');
            name = currLine.substr(0, commaPosition);      // CS101
            currLine = currLine.substr(commaPosition + 1); // 1170 TMCB)

            string room;
            parenPosition = currLine.find(')');
            room = currLine.substr(0, parenPosition); // 1170 TMCB

            Cr cr(name, room);
            crVec.push_back(cr);
        }
    }

    out << endl
        << endl;

    out << "Vectors:" << endl;
    for (size_t i = 0; i < snapVec.size(); i++)
    {
        out << snapVec[i] << endl;
    }
    for (size_t i = 0; i < csgVec.size(); i++)
    {
        out << csgVec[i] << endl;
    }
    for (size_t i = 0; i < cdhVec.size(); i++)
    {
        out << cdhVec[i] << endl;
    }
    for (size_t i = 0; i < crVec.size(); i++)
    {
        out << crVec[i] << endl;
    }
    out << endl;

    out << "Course Grades" << endl;
    for (size_t i = 0; i < csgVec.size(); i++)
    {
        out << csgVec[i].getCourseName() << ","
            << findStudentNameByID(csgVec[i].getStudentID(), snapVec) << ","
            << csgVec[i].getStudentGrade() << endl;
    }

    return 0;
}

/*-------------------------------Function Definitions-------------------------------*/
string findStudentNameByID(int ID, const vector<Snap> &snapVec)
{
    for (size_t i = 0; i < snapVec.size(); i++)
    {
        int studentID = snapVec[i].getStudentID();
        if (studentID == ID)
        {
            return snapVec[i].getStudentName();
        }
    }
    string errMsg = "Not Found";
    throw(errMsg);
}