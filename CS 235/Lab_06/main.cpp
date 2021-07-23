/**
 * Zarin Loosli - date
**/
#include <iostream>
#include <fstream>
#include <string>

#include "Stack.h"
#include "Vector.h"
#include "Queue.h"

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
    int testArray[] = {1, 2, 3, 4};
    // Deque<int> myDeque(testArray, 4);
    // int testArray1[] = {1, 2, 3};
    // Deque<int> myDeque1(testArray1, 3);
    // int testArray2[] = {1, 2, 3, 4, 5};
    // Deque<int> myDeque2 = Deque<int>(testArray2, 5);
    // Deque<int> emptyDeque;

    // myDeque.pop_front();
    // myDeque1.push_front(-5);
    // myDeque.push_front(-5);
    // cout << "myDeque " << myDeque << endl;
    // cout << "myDeque1 " << myDeque1 << endl;
    // myDeque.pop_back();
    // myDeque.push_front(-5);
    // myDeque.push_front(-6);
    // myDeque.push_front(-7);
    // cout << myDeque.size() << endl;
    // cout << "myDeque " << myDeque << endl;
    // cout << "myDeque1 " << myDeque1 << endl;
    // cout << "myDeque2 " << myDeque2 << endl;

    // cout << emptyDeque.empty() << endl;
    // emptyDeque.push_back(0);
    // cout << emptyDeque.empty() << endl;
    // emptyDeque.push_back(0);
    // cout << emptyDeque.empty() << endl;
    // emptyDeque.pop_back();
    // emptyDeque.pop_back();
    // emptyDeque.push_back(1);
    // cout << emptyDeque.empty() << endl;

    Stack<int> myStack;
    cout << myStack << endl;
    myStack.push(1);
    myStack.push(2);
    myStack.push(3);
    myStack.push(4);
    cout << myStack << endl;
    cout << myStack.size() << endl;
    myStack.pop();
    cout << myStack << endl;

    return 0;
}

/*------------------------------------------------ Function Definitions ------------------------------------------------*/
