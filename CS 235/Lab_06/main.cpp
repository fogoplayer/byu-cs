/**
 * Zarin Loosli - date
**/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Station.h"
#include "Car.h"

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
 * @param int char* argv[] the file address | other arguments
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

    // -------------------------------------------------------------------------------------------------------------
    Station<Car> station;

    string currLine;
    while (getline(in, currLine))
    {
        size_t delimiterIndex = currLine.find(":");
        string command = currLine.substr(0, delimiterIndex);
        string argument = currLine.substr(delimiterIndex + 1);
        out << currLine;

        if (command == "Add")
        {
            istringstream is(argument);
            string target;
            unsigned int value;
            is >> target >> value;

            if (target == "station")
            {

                out << " " << station.addCar(Car(value)) << endl;
            }
            else if (target == "queue")
            {
                out << " " << station.addQueue() << endl;
            }
            else if (target == "stack")
            {
                out << " " << station.addStack() << endl;
            }
        }

        if (command == "Remove")
        {
            istringstream is(argument);
            string target;
            unsigned int value;
            is >> target >> value;

            if (target == "station")
            {
                out << " " << station.removeCar() << endl;
            }
            else if (target == "queue")
            {
                out << " " << station.removeQueue() << endl;
            }
            else if (target == "stack")
            {
                out << " " << station.removeStack() << endl;
            }
        }

        if (command == "Top")
        {
            istringstream is(argument);
            string target;
            unsigned int value;
            is >> target >> value;

            if (target == "station")
            {
                out << " " << station.topCar() << endl;
            }
            else if (target == "queue")
            {
                out << " " << station.topQueue() << endl;
            }
            else if (target == "stack")
            {
                out << " " << station.topStack() << endl;
            }
        }

        if (delimiterIndex == string::npos)
        {
            istringstream is(argument);
            string target;
            unsigned int value;
            is >> target >> value;

            if (command == "Train")
            {
                out << station.trainString() << endl;
            }
            else if (command == "Queue")
            {
                out << station.queueString() << endl;
            }
            else if (command == "Stack")
            {
                out << station.stackString() << endl;
            }
        }

        if (command == "Size")
        {
            istringstream is(argument);
            string target;
            unsigned int value;
            is >> target >> value;

            if (target == "train")
            {
                out << " " << station.sizeTrain() << endl;
            }
            else if (target == "queue")
            {
                out << " " << station.sizeQueue() << endl;
            }
            else if (target == "stack")
            {
                out << " " << station.sizeStack() << endl;
            }
        }

        if (command.substr(0, 4) == "Find")
        {
            string searchResult;

            istringstream os(command.substr(4));
            int arg;
            os >> arg;
            Car searchCar(arg);

            searchResult = station.queueFind(searchCar);
            if (searchResult != "false")
            {
                out << " Queue[" + searchResult + "]" << endl;
                continue;
            }

            searchResult = station.stackFind(searchCar);
            if (searchResult != "false")
            {
                out << " Stack[" + searchResult + "]" << endl;
                continue;
            }

            searchResult = station.trainFind(searchCar);
            if (searchResult != "false")
            {
                out << " Train[" + searchResult + "]" << endl;
                continue;
            }

            out << " Not Found!" << endl;
        }
    }

    return 0;
}

/*------------------------------------------------ Function Definitions ------------------------------------------------*/
