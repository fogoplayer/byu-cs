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
            strList.clear();
        }
        else if (command == "Empty")
        {
            strList.empty();
        }
        else if (command == "Delete")
        {
            try
            {
                strList.pop_front();
            }
            catch (string e)
            {
                out << e << endl;
                cout << e << endl;
            }
        }
        else if (command == "First")
        {
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
            strList.push_front("1");
        }
        else if (command == "PrintList")
        {
            out << strList.toString();
            cout << strList.toString() << endl;
        }
        else if (command == "Remove")
        {
            strList.remove("1");
        }
        else if (command == "Reverse")
        {
            try
            {
                strList.reverse();
            }
            catch (string e)
            {
                out << e << endl;
                cout << e << endl;
            }
        }
        else if (command == "Size")
        {
            strList.size();
        }
    }

    return 0;
}

/*------------------------------------------------ Function Definitions ------------------------------------------------*/
