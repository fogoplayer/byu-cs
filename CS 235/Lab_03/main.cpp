/**
 * Zarin Loosli - 7/9/21
**/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "LinkedList.h"
// #include "LinkedListInterface.h"

using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

/*------------------------------------------------ Function Declarations ------------------------------------------------*/

/**
 * main
 * @param argc the number of arguments passed to main
 * @param argv[] the file address | input file | output file
**/
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

    // Instatiate List ----------------------------------------------------------------------------------------------------
    LinkedList<string> strList;

    // Process file -------------------------------------------------------------------------------------------------------
    string currLineString = "";
    while (getline(in, currLineString)) // Loop through each line of input
    {
        // Extract command
        istringstream currLine(currLineString);
        string command = "";
        currLine >> command;

        // Execute command
        if (command == "Clear")
        {
            out << "Clear ";
            strList.clear();
            out << " OK" << endl;
            cout << " OK" << endl;
        }

        else if (command == "Empty")
        {
            out << "Empty ";
            out << strList.empty() << endl;
            cout << "Empty? " << strList.empty() << endl;
        }

        else if (command == "Delete")
        {
            out << "Delete ";
            try
            {
                strList.pop_front();
                out << endl;
            }
            catch (string e)
            {
                out << e << endl;
                cout << e << endl;
            }
        }

        else if (command == "First")
        {
            out << "First ";
            try
            {
                out << strList.front() << endl;
                cout << strList.front() << endl;
            }
            catch (string e)
            {
                out << e << endl;
                cout << e << endl;
            }
        }

        else if (command == "Insert")
        {
            out << "Insert " << endl;
            string nodeData = "";
            while (currLine >> nodeData)
            {
                strList.push_front(nodeData);
            }
        }

        else if (command == "PrintList")
        {
            out << "PrintList ";
            out << strList.toString() << endl;
            cout << strList.toString() << endl;
        }

        else if (command == "Remove")
        {
            out << "Remove " << endl;
            string nodeData = "";
            while (currLine >> nodeData)
            {
                strList.remove(nodeData);
            }
        }

        else if (command == "Reverse")
        {
            out << "Reverse ";
            try
            {
                strList.reverse();
                out << endl;
            }
            catch (string e)
            {
                out << e << endl;
                cout << e << endl;
            }
        }

        else if (command == "Size")
        {
            out << "Size ";
            out << strList.size() << endl;
            cout << strList.size() << endl;
        }
    }

    return 0;
}

/*------------------------------------------------ Function Definitions ------------------------------------------------*/
