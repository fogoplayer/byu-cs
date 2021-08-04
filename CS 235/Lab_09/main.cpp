/**
 * Zarin Loosli - 8/3/21
**/
#include <iostream>
#include <fstream>
#include <string>

#include "HashMap.h"
#include "Set.h"

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

    HashMap<string, string> pokemonMap = HashMap<string, string>();
    HashMap<string, string> movesMap = HashMap<string, string>();

    string command;
    while (in >> command)
    {
        out << command;

        if (command == "Set:")
        {
            Set<string> stringSet;

            string setValues;
            getline(in, setValues);
            out << setValues << endl;
            istringstream setValuesStream(setValues);

            while (setValuesStream >> command)
            {
                stringSet.insert(command);
            }

            out << "  [" << stringSet << "]" << endl;
        }

        else if (command == "Pokemon:") // Input command
        {
            string key;
            string val;
            in >> key >> val;
            pokemonMap[key] = val;
            out << " " << key << " " << val;
        }

        else if (command == "Pokemon") // Print command
        {
            out << ": " << pokemonMap;
        }

        else if (command == "Move:") // Input command
        {
            string key;
            string val;
            in >> key >> val;
            movesMap[key] = val;
            out << " " << key << " " << val;
        }

        else if (command == "Moves") // Print command
        {
            out << ": " << movesMap;
        }

        out << endl;
    }

    pokemonMap.~HashMap();

    return 0;
}

/*------------------------------------------------ Function Definitions ------------------------------------------------*/
