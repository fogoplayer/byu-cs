/**
 * Zarin Loosli - 6/30/21
**/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

#include "main.h"

using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

/**
 * main
 * @param argc the number of arguments passed to main
 * @param *argv[] the file address | input file | output file
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
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }

    // Try to open output file
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    //Load in counts
    int numOfStudents;
    int numOfExams;
    in >> numOfStudents >> numOfExams;
    in.ignore(std::numeric_limits<int>::max(), '\n');

    //Fill in arrays
    string *students = new string[numOfStudents];
    int **exams = createExamArray(numOfStudents, numOfExams);
    cout << "Arrays should be blank" << endl;
    printArrays(students, numOfStudents, exams, numOfExams);
    for (int i = 0; i < numOfStudents; i++)
    {
        string singleStudentsData;
        getline(in, singleStudentsData);
        addSingleStudentsData(singleStudentsData, i, students, exams);
    }
    cout << "Arrays should be filled in" << endl;
    printArrays(students, numOfStudents, exams, numOfExams);

    return 0;
}

//------------------------------------------------ Function Definitions -------------------------------------------------//
int **createExamArray(int numOfStudents, int numOfExams)
{
    int** outerArray = new int*[numOfStudents];
    for (int i = 0; i < numOfStudents; i++)
    {
        outerArray[i] = new int[numOfExams];
    }
    return outerArray;
}

void addSingleStudentsData(string data, int studentIndex, string* students, int** exams)
{
    cout << data << endl;

    // Student name
    size_t p = 0;
    while ((data[p] != ' ') || (data[p+1] != ' '))  //Looks for the two consecutive spaces after a user's name
    {
        ++p;
    }
    students[studentIndex] = data.substr(0,p);

    // Scores
    while (!isdigit(data[p])) ++p;	// data[p] is the first digit
    data = data.substr(p);
    
    istringstream scores(data);
    int i = 0;
    int score = 9999;
    
    while(scores >> score)
    {
        // int score = 999999;
        // scores >> score;
        exams[studentIndex][i] = score;
        i++;
    }

    // TODO close file streams
    // TODO delete students
    // TODO delete exams (recursive)

    return;
}

void printArrays(string* studentsArray, int studentsCount, int** examsArray, int examsCount)
{
    for (size_t i = 0; i < studentsCount; i++)
    {
        cout << studentsArray[i];
        for (size_t j = 0; j < examsCount; j++)
        {
            cout << " " << examsArray[i][j];
        }
        cout << endl;
    }
    cout << endl;
}