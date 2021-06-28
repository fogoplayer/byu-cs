#ifndef MAIN_H_
#define MAIN_H_

#include <string>
using namespace std;

/**
 * @param numOfStudents the number of students in the input file
 * @param numOfExams the number of exams in the input file
 * @return a pointer to a 2D array ready to be populated with data from the stream
**/
int **createExamArray(int numOfStudents, int numOfExams);

/**
 * @param data a line from the source file
 * @param students a pointer to the students array
 * @param exams a pointer to the exams array
 * @return void
**/
void addSingleStudentsData(string data, int studentIndex, string* students, int** exams);

/**
 * @param studentsArray pointer to array of students
 * @param studentsCount number of students
 * @param examsArray pointer to 2D array of exams
 * @param examsCount number of exams
**/
void printArrays(string* studentsArray, int studentsCount, int** examsArray, int examsCount);

#endif