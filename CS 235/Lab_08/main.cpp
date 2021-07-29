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

        cout << currLine << endl;

        // Int ------------------------------------------------------------------------------------------------------------
        if (currLine == "INT")
        {
            Bst<int> bstInt;
            while (getline(in, currLine))
            {
                string command;
                istringstream is(currLine);
                is >> command;

                if (command == "add")
                {
                    int arg;
                    is >> arg;
                    bstInt.addNode(arg);
                }

                else
                {
                    break;
                }
            }
        }

        // String ---------------------------------------------------------------------------------------------------------
        else if (currLine == "STRING")
        {
            Bst<string> bstString;
            if (false)
            {
            }
            else
            {
                break;
            }
        }
    }

    return 0;
}

/*------------------------------------------------ Function Definitions ------------------------------------------------*/
