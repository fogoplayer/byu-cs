#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Student {
public:
	Student(string name = "not initialized", double gpa = 0.0);
	void SetName(string studentName);
	void SetGPA(double newGPA);
	string ToString() const;
private:
	string name;
	double gpa;
};

Student::Student(string initialName, double initialGPA) {
	name = initialName;
	gpa = initialGPA;
}

void Student::SetName(string inputName) {
	name = inputName;
}

void Student::SetGPA(double newGPA) {
	gpa = newGPA;
}

string Student::ToString() const {
   return name + " has a GPA of " + to_string(gpa);
}

int main() {
	vector<Student*> students;
	string selectedMenuOption = "quit";

	do {
	   cout << "Enter Option: ";
	   cin >> selectedMenuOption;
	   
	   // Add
	   if(selectedMenuOption == "add") {
	      string newStudentName = "";
	      double newStudentGPA = 0.0;
	      
	      cout << "Student name: ";
	      cin >> newStudentName;
	      cout << endl << newStudentName <<"'s GPA: ";
	      cin >> newStudentGPA;
	      cout << endl;
	      
	      Student* newStudent = new Student(newStudentName, newStudentGPA);
	      students.push_back(newStudent);
	   }
	   
	   // Print
	   else if(selectedMenuOption == "print"){
	      for(unsigned int i = 0; i < students.size(); ++i) {
	         cout << i << ": " << students[i]->ToString() << endl;
	      }
	      cout << endl;
	   }
	   
	   // Drop
	   else if(selectedMenuOption == "drop") {
	      int indexToDrop = -1;
	      cout << "Index of student to drop: ";
	      cin >> indexToDrop;
	      cout << endl;
	      
	      delete students[indexToDrop];
	      students.erase(students.begin() + indexToDrop);
	   }
	   
	} while(selectedMenuOption != "quit");

	return 0;
}