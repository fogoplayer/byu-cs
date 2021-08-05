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

    HashMap<string, string> pokemonMap;
    HashMap<string, string> movesMap;
    HashMap<string, Set<string>> effective;
    HashMap<string, Set<string>> ineffective;

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

        else if (command == "Effective:")
        {
            string key;
            in >> key;
            out << " " << key;

            string rest;
            getline(in, rest);
            istringstream restStream(rest);

            string currSetVal;
            while (restStream >> currSetVal)
            {
                effective[key].insert(currSetVal);
                out << " " << currSetVal;
            }
        }

        else if (command == "Effectivities")
        {
            out << ": " << effective;
        }

        else if (command == "Ineffective:")
        {
            string key;
            in >> key;
            out << " " << key;

            string rest;
            getline(in, rest);
            istringstream restStream(rest);

            string currSetVal;
            while (restStream >> currSetVal)
            {
                ineffective[key].insert(currSetVal);
                out << " " << currSetVal;
            }
        }

        else if (command == "Ineffectivities")
        {
            out << ": " << ineffective;
        }

        else if (command == "Battle:")
        {
            string pokemon1, move1, pokemon2, move2;
            in >> pokemon1 >> move1 >> pokemon2 >> move2;
            out << " " << pokemon1 << " " << move1 << " " << pokemon2 << " " << move2 << endl;
            out << "  " << pokemon1 << " (" << move1 << ") vs " << pokemon2 << " (" << move2 << ")" << endl;

            string pokemon1Type = pokemonMap[pokemon1];
            string pokemon2Type = pokemonMap[pokemon2];
            string move1Type = movesMap[move1];
            string move2Type = movesMap[move2];
            string effectivity;

            out << "  " << pokemon1 << " is a " << pokemon1Type << " type Pokemon." << endl;
            out << "  " << pokemon2 << " is a " << pokemon2Type << " type Pokemon." << endl;
            out << "  " << move1 << " is a " << move1Type << " type move." << endl;
            out << "  " << move2 << " is a " << move2Type << " type move." << endl;

            // Move info
            out << "  " << move1 << " is super effective against [" << effective[move1Type] << "] type Pokemon." << endl;
            out << "  " << move1 << " is ineffective against [" << ineffective[move1Type] << "] type Pokemon." << endl;

            // Determine effectivity
            if (effective[move1Type].count(pokemon2Type) > 0)
            {
                effectivity = "super effective";
            }
            else if (ineffective[move1Type].count(pokemon2Type) > 0)
            {
                effectivity = "ineffective";
            }
            else
            {
                effectivity = "effective";
            }

            out << "  " << pokemon1 << "'s " << move1 << " is " << effectivity << " against " << pokemon2 << endl;

            // Move info
            out << "  " << move2 << " is super effective against [" << effective[move2Type] << "] type Pokemon." << endl;
            out << "  " << move2 << " is ineffective against [" << ineffective[move2Type] << "] type Pokemon." << endl;

            // Determine effectivity
            if (effective[move2Type].count(pokemon1Type) > 0)
            {
                effectivity = "super effective";
            }
            else if (ineffective[move2Type].count(pokemon1Type) > 0)
            {
                effectivity = "ineffective";
            }
            else
            {
                effectivity = "effective";
            }

            out << "  " << pokemon2 << "'s " << move2 << " is " << effectivity << " against " << pokemon1 << endl;

            // Damage done
            int damage1To2 = effective[move1Type].count(pokemon2Type) - ineffective[move1Type].count(pokemon2Type);
            int damage2To1 = effective[move2Type].count(pokemon1Type) - ineffective[move2Type].count(pokemon1Type);

            if ((damage1To2 - damage2To1) > 0)
            {
                out << "  In the battle between " << pokemon1 << " and " << pokemon2 << ", " << pokemon1 << " wins!";
            }
            else if ((damage1To2 - damage2To1) < 0)
            {
                out << "  In the battle between " << pokemon1 << " and " << pokemon2 << ", " << pokemon2 << " wins!";
            }
            else
            {
                out << "  The battle between " << pokemon1 << " and " << pokemon2 << " is a tie.";
            }

            out << endl
                << endl;
        }

        out << endl;
    }

    return 0;
}

/*------------------------------------------------ Function Definitions ------------------------------------------------*/
