/**
 * Zarin Loosli - 6/30/21
**/
#include <iostream>
#include <iomanip>
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
    // cout << "Arrays should be blank" << endl;
    // printArrays(students, numOfStudents, exams, numOfExams);
    for (int i = 0; i < numOfStudents; i++)
    {
        string singleStudentsData;
        getline(in, singleStudentsData);
        addSingleStudentsData(singleStudentsData, i, students, exams);
    }
    cout << "Arrays should be filled in" << endl;
    printArrays(students, numOfStudents, exams, numOfExams);

    //Generate output file
    printStudentScores(out, students, numOfStudents, exams, numOfExams);
    printExamAverages(out, students, numOfStudents, exams, numOfExams);
    printStudentGrades(out, students, numOfStudents, exams, numOfExams);
    printExamGrades(out, students, numOfStudents, exams, numOfExams);

    // Cleanup
    delete[] students;
    delete2dArray(exams, numOfStudents);
    in.close();
    out.close();

    return 0;
}

//------------------------------------------------ Function Definitions -------------------------------------------------//
int **createExamArray(int numOfStudents, int numOfExams)
{
    int **outerArray = new int *[numOfStudents];
    for (int i = 0; i < numOfStudents; i++)
    {
        outerArray[i] = new int[numOfExams];
    }
    return outerArray;
}

void addSingleStudentsData(string data, int studentIndex, string *students, int **exams)
{
    cout << data << endl;
    size_t p = 0;
    while (!isdigit(data[p]))
    {
        ++p; // data[p] is the first digit
    }
    // Student name
    string beforeScores = data.substr(0, p);
    istringstream name(beforeScores);

    string partOfName = "";
    while (name >> partOfName)
    {
        students[studentIndex] += partOfName + " ";
    }
    students[studentIndex].substr(0, students[studentIndex].size() - 2);

    // Scores
    data = data.substr(p);

    istringstream scores(data);
    int i = 0;
    int score = 9999;

    while (scores >> score)
    {
        // int score = 999999;
        // scores >> score;
        exams[studentIndex][i] = score;
        i++;
    }

    return;
}

void printArrays(string *studentsArray, int studentsCount, int **examsArray, int examsCount)
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

int *calcAverageExamScores(int studentsCount, int **examsArray, int examsCount)
{
    int *averageExamScores = new int[examsCount];
    for (int i = 0; i < examsCount; i++) // Loop through each exam
    {
        double averageScore = 0;
        for (size_t j = 0; j < studentsCount; j++)
        {
            averageScore += examsArray[j][i];
        }
        averageScore /= studentsCount;
        averageExamScores[i] = averageScore;
    }
    return averageExamScores;
}

void delete2dArray(int **pointer, int numRows)
{
    for (size_t i = 0; i < numRows; i++)
    {
        delete[] pointer[i]; // Delete cells
    }
    delete[] pointer; // Delete rows
}

// Output Functions -------------------------------------------------------------------------------------------------------
void printStudentScores(ostream &output, string *studentsArray, int studentsCount, int **examsArray, int examsCount)
{
    output << "Student Scores:\n";
    for (size_t i = 0; i < studentsCount; i++)
    {
        output << setw(20) << right << studentsArray[i] << " ";
        for (size_t j = 0; j < examsCount; j++)
        {
            output << fixed << setprecision(0) << setw(6) << examsArray[i][j];
        }
        output << endl;
    }
}

void printExamAverages(ostream &output, string *studentsArray, int studentsCount, int **examsArray, int examsCount)
{
    output << "Exam Averages:" << endl;
    for (int i = 0; i < examsCount; i++) // Loop through each exam
    {
        // Calculate average score
        double averageScore = 0;
        for (size_t j = 0; j < studentsCount; j++)
        {
            averageScore += examsArray[j][i];
        }
        averageScore /= studentsCount;

        // Print average score
        string examName = "Exam " + to_string(i + 1) + " Average = ";
        output << setw(21) << right << examName;
        output << fixed << setprecision(1) << setw(6) << averageScore << endl;
    }
}

void printStudentGrades(ostream &output, string *studentsArray, int studentsCount, int **examsArray, int examsCount)
{
    // Get array of average scores
    int *averageExamScores = calcAverageExamScores(studentsCount, examsArray, examsCount);

    // Determine letter grades and output
    output << "Student Exam Grades:" << endl;
    for (size_t i = 0; i < studentsCount; i++)
    {
        output << setw(20) << right << studentsArray[i];
        for (size_t j = 0; j < examsCount; j++)
        {
            char letterGrade;
            if (examsArray[i][j] - averageExamScores[j] > 15)
            {
                letterGrade = 'A';
            }
            else if (examsArray[i][j] - averageExamScores[j] > 5)
            {
                letterGrade = 'B';
            }
            else if (examsArray[i][j] - averageExamScores[j] > -5)
            {
                letterGrade = 'C';
            }
            else if (examsArray[i][j] - averageExamScores[j] > -15)
            {
                letterGrade = 'D';
            }
            else
            {
                letterGrade = 'E';
            }
            output << fixed << setprecision(0) << setw(6) << examsArray[i][j] << "(" << letterGrade << ")";
        }
        output << endl;
    }

    delete[] averageExamScores;
}

void printExamGrades(ostream &output, string *studentsArray, int studentsCount, int **examsArray, int examsCount)
{
    // Get array of average scores
    int *averageExamScores = calcAverageExamScores(studentsCount, examsArray, examsCount);

    // Create array to store totals
    int **examGrades = new int *[examsCount];
    for (size_t i = 0; i < examsCount; i++)
    {
        examGrades[i] = new int[5];    // Array is initialized so all values are 0
        for (size_t j = 0; j < 5; j++) // For some reason not all values were being set to 0 so I did it manually
        {
            examGrades[i][j] = 0;
        }
    }

    /* 
        examGrades structure
                [A][B][C][D][E]
        [Exam 1][ ][ ][ ][ ][ ]
        [Exam 2][ ][ ][ ][ ][ ]
        [Exa...][ ][ ][ ][ ][ ]
    */

    // Determine letter grades and output
    for (size_t i = 0; i < studentsCount; i++)
    {
        for (size_t j = 0; j < examsCount; j++)
        {
            if (examsArray[i][j] - averageExamScores[j] > 15)
            {
                examGrades[j][0]++; // A
            }
            else if (examsArray[i][j] - averageExamScores[j] > 5)
            {
                examGrades[j][1]++; // B
            }
            else if (examsArray[i][j] - averageExamScores[j] > -5)
            {
                examGrades[j][2]++; // C
            }
            else if (examsArray[i][j] - averageExamScores[j] > -15)
            {
                examGrades[j][3]++; // D
            }
            else
            {
                examGrades[j][4]++; // E
            }
        }
    }

    // Print scores
    output << "Exam Grades:" << endl;
    for (int i = 0; i < examsCount; i++) // Loop through each exam
    {
        string examName = "Exam  " + to_string(i + 1);
        output << setw(11) << right << examName;
        for (size_t j = 0; j < 5; j++) // Loop through each letter grade
        {
            output << fixed << setprecision(1) << setw(5) << examGrades[i][j] << "(";

            switch (j) // Display a letter grade next to the count
            {
            case 0:
                output << 'A';
                break;

            case 1:
                output << 'B';
                break;

            case 2:
                output << 'C';
                break;

            case 3:
                output << 'D';
                break;

            case 4:
                output << 'E';
                break;

            default:
                break;
            }

            output << ")";
        }

        output << endl;
    }

    delete[] averageExamScores;
    delete2dArray(examGrades, examsCount);
}