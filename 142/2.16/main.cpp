#include <iostream>
#include <string>      // Supports use of "string" data type
using namespace std;

int main() {
   int    userInt = 0;
   double userDouble = 0.0;
   // FIXME: Define char and string variables
   char userChar = '\0';
   string userString = "";   
   
   //Int
   cout << "Enter integer: ";
   cin  >> userInt;
   cout << endl;
   
   //double
   cout << "Enter double: ";
   cin  >> userDouble;
   cout << endl;
   
   //Int
   cout << "Enter character: ";
   cin  >> userChar;
   cout << endl;
   
   //Int
   cout << "Enter string: ";
   cin  >> userString;
   cout << endl;
   
   // FIXME (1): Finish reading other items into variables, then output the four values on a single line separated by a space
   cout << userInt << " " << userDouble << " " << userChar << " " << userString << endl;
   
   // FIXME (2): Output the four values in reverse
   cout << userString << " " << userChar << " " << userDouble << " " << userInt << endl;
   
   // FIXME (3): Cast the double to an integer, and output that integer
   cout << userDouble << " cast to an integer is " << static_cast<int>(userDouble) << endl;

   return 0;
}