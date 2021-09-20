#include <iostream>
using namespace std;

int main() {
   int userNum = 0;
   int userNum2 = 0;

   cout << "Enter integer: ";
   cin  >> userNum;
   cout << endl;
   
   /* Type your code here */
   cout << "You entered: " << userNum << endl;
   cout << userNum << " squared is " << userNum * userNum << endl;
   cout << "And " << userNum << " cubed is " << userNum * userNum * userNum << "!!" << endl;
   
   cout << "Enter another integer: ";
   cin  >> userNum2;
   cout << endl;
   cout << userNum << " + " << userNum2 << " is " << userNum + userNum2 << endl;
   cout << userNum << " * " << userNum2 << " is " << userNum * userNum2 << endl;
   
   return 0;
}