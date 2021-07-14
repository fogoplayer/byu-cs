/**
 * Zarin Loosli - 7/9/21
 * Takes in a file, processes the commands in that file to manipulate a 
 * string list, and produces an output for a new file
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
#if 1
    // Iterator Tests

    LinkedList<string> StrList;
    StrList.push_front("is");
    StrList.push_front("name");
    StrList.push_front("my");
    StrList.push_front("Hello");

    cout << StrList.toString() << endl;
    cout << *StrList.begin() << " " << *++StrList.begin() << endl;
    StrList.insert(StrList.find(StrList.begin(), StrList.end(), "name"), "BOO");
    StrList.insert_after(StrList.find(StrList.begin(), StrList.end(), "name"), "BAH");
    cout << StrList << endl;
    StrList.erase(StrList.begin());
    StrList.erase(StrList.find(StrList.begin(), StrList.end(), "BOO"));
    cout << StrList << endl;
    StrList.replace(StrList.begin(), StrList.end(), "BAH", "probably");
    cout << StrList << endl;

#endif
#if 0
    // Instatiate List ----------------------------------------------------------------------------------------------------
    LinkedList<string> StrList;

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
            StrList.clear();
            out << "OK" << endl;
            cout << "OK" << endl;
        }

        else if (command == "Empty")
        {
            out << "Empty ";
            out << (StrList.empty() ? "true" : "false") << endl;
            cout << "Empty? " << StrList.empty() << endl;
        }

        else if (command == "Delete")
        {
            out << "Delete ";
            try // Try-catch block to handle empty array
            {
                StrList.pop_front();
                out << "OK" << endl;
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
            try // Try-catch block to handle empty array
            {
                out << StrList.front() << endl;
                cout << StrList.front() << endl;
            }
            catch (string e)
            {
                out << e << endl;
                cout << e << endl;
            }
        }

        else if (command == "Insert")
        {
            out << "Insert";
            string nodeData = "";
            while (currLine >> nodeData)
            {
                out << " " << nodeData;
                StrList.push_front(nodeData);
            }
            out << endl;
        }

        else if (command == "PrintList")
        {
            out << "PrintList";
            out << StrList.toString() << endl;
            cout << StrList.toString() << endl;
        }

        else if (command == "Remove")
        {
            out << "Remove";
            string nodeData = "";
            while (currLine >> nodeData)
            {
                out << " " << nodeData;
                StrList.remove(nodeData);
            }
            out << endl;
        }

        else if (command == "Reverse")
        {
            out << "Reverse ";
            try // Try-catch block to handle empty array
            {
                StrList.reverse();
                out << "OK" << endl;
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
            out << StrList.size() << endl;
            cout << StrList.size() << endl;
        }

        else
        {
            out << command << endl; // Print out double-linked commands for diffchecker
        }
    }

    // Memory Cleanup
    StrList.clear();
#endif
    return 0;
}

/*------------------------------------------------ Function Definitions ------------------------------------------------*/
