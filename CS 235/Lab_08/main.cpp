/**
 * Zarin Loosli - 7/27/21
**/
#include <iostream>
#include <fstream>
#include <string>

#include "BST.h"

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
 * @param int argc the number of arguments passed to main
 * @param int char* argv[] the file address | input file | output file
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

    string currLine;
    while (getline(in, currLine))
    {

        string command;
        istringstream is(currLine);
        is >> command;
        out << command;

        // Int ------------------------------------------------------------------------------------------------------------
        if (command == "INT")
        {
            Bst<int> bstInt;
            out << " true" << endl;
            while (getline(in, currLine))
            {
                // Print out command
                istringstream is(currLine);
                is >> command;
                out << command;

                // Add
                if (command == "add")
                {
                    int arg;
                    is >> arg;
                    out << " " << arg << " " << (bstInt.addNode(arg) ? "true" : "false");
                }

                // Remove
                else if (command == "remove")
                {
                    int arg;
                    is >> arg;
                    out << " " << arg << " " << (bstInt.removeNode(arg) ? "true" : "false");
                }

                // Clear
                else if (command == "clear")
                {
                    out << " " << (bstInt.clearTree() ? "true" : "false");
                }

                // Size
                else if (command == "size")
                {
                    out << " " << bstInt.size();
                }

                // Print
                else if (command == "print")
                {
                    out << ":" << bstInt.toString();
                }

                // Find
                else if (command == "find")
                {
                    int arg;
                    is >> arg;
                    out << " " << arg << " " << bstInt.find(arg);
                }

                // Exceptions
                else
                {
                    break;
                }

                out << endl;
            }
        }

        // String ---------------------------------------------------------------------------------------------------------
        Bst<string> bstString;
        out << " true" << endl;
        while (getline(in, currLine))
        {
            // Print out command
            istringstream is(currLine);
            is >> command;
            out << command;

            // Add
            if (command == "add")
            {
                string arg;
                is >> arg;
                out << " " << arg << " " << (bstString.addNode(arg) ? "true" : "false");
            }

            // Remove
            else if (command == "remove")
            {
                string arg;
                is >> arg;
                out << " " << arg << " " << (bstString.removeNode(arg) ? "true" : "false");
            }

            // Clear
            else if (command == "clear")
            {
                out << " " << (bstString.clearTree() ? "true" : "false");
            }

            // Size
            else if (command == "size")
            {
                out << " " << bstString.size();
            }

            // Print
            else if (command == "print")
            {
                out << ":" << bstString.toString();
            }

            // Find
            else if (command == "find")
            {
                string arg;
                is >> arg;
                out << " " << arg << " " << bstString.find(arg);
            }

            // Exceptions
            else
            {
                break;
            }

            out << endl;
        }
    }

    return 0;
}

/*------------------------------------------------ Function Definitions ------------------------------------------------*/
