#include <iostream>
using namespace std;

int main() {
   char triangleChar = ' ';
   int triangleHeight = 0;

   cout << "Enter a character: " << endl;
   cin >> triangleChar;
   
   cout << "Enter triangle height: " << endl;
   cin >> triangleHeight;
   
   for (int i = 1; i <= triangleHeight; ++i) {  //Starting at 1 so that i is the row number/number of chars in a row
      for (int j = 1; j <= i; ++j) {   //Each row gets longer as you get further into the rows
         cout << triangleChar << " ";
      }
      cout << endl;
   }
   
   return 0;
}