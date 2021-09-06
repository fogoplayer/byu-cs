/**
 * Zarin Loosli - 8/10/21
**/
#include <iostream>
#include <fstream>
#include <string>

#include "QuickSort.h"

using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

/*------------------------------------------------ Function Declarations ------------------------------------------------*/

void newQuickSort(istream &in, ostream &out);

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

    // Execute Commands ---------------------------------------------------------------------------------------------------
    string command;
    in >> command;
    out << command;
    newQuickSort(in, out);

    return 0;
}

/*------------------------------------------------ Function Definitions ------------------------------------------------*/

void newQuickSort(istream &in, ostream &out)
{
    string command;
    int capacity;

    in >> capacity;
    out << " " << capacity << " OK" << endl;

    QuickSort<int> qs(capacity);

    while (in >> command)
    {
        out << command;

        if (command == "Capacity")
        {
            out << " "
                << qs.capacity();
        }

        else if (command == "Clear")
        {
            qs.clear();
            out << " OK";
        }

        else if (command == "AddToArray")
        {
            getline(in, command);
            istringstream is(command);

            int arg;

            // First one
            is >> arg;
            out << "  " << arg;
            qs.addElement(arg);

            // Others
            while (is >> arg)
            {
                out << "," << arg;
                qs.addElement(arg);
            }

            out << " OK";
        }

        else if (command == "PrintArray")
        {
            out << qs;
        }

        else if (command == "Size")
        {
            out << " " << qs.size();
        }

        else if (command == "MedianOfThree")
        {
            size_t arg1, arg2;
            in >> arg1 >> arg2;
            out << " " << arg1 << "," << arg2;
            out << " = " << qs.medianOfThree(arg1, arg2);
        }

        else if (command == "Partition")
        {
            int arg1, arg2, arg3;
            in >> arg1 >> arg2 >> arg3;
            out << " " << arg1 << "," << arg2 << "," << arg3;
            out << " = " << qs.partition(arg1, arg2, arg3);
        }

        else if (command == "SortAll")
        {
            qs.sortAll();
            out << " OK";
        }

        else if (command == "Sort")
        {
            size_t arg1, arg2;
            in >> arg1 >> arg2;
            out << " " << arg1 << "," << arg2;
            qs.sort(arg1, arg2);
            out << " OK";
        }

        // Insert here

        else if (command == "QuickSort")
        {
            newQuickSort(in, out);
            break;
        }

        out << endl;
    }
}
