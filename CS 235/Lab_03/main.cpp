/**
 * Zarin Loosli - 7/9/21
**/
#include <iostream>
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

    LinkedList<string> intList;
    intList.push_front("Hello");
    intList.pop_front();
    intList.front();
    intList.empty();
    intList.remove("Hello");
    intList.clear();
    intList.reverse();
    intList.size();
    intList.toString();
    return 0;
}

/*------------------------------------------------ Function Definitions ------------------------------------------------*/
