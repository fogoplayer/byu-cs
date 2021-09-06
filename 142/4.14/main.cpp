#include <iostream>
#include <string> // Note: This library is needed to use the string type
using namespace std;

int main() {

   /* Type your code here. */
   string abbr = "";
   
   cout << "Input an abbreviation: ";
   cin >> abbr;
   cout << endl;
   
   if (abbr == "BFF"){
      cout << "best friends forever";
   }else if(abbr == "IMHO"){
      cout << "in my humble opinion";
   }else if (abbr == "IDK") {
      cout << "I don't know";
   }else if (abbr == "LOL") {
      cout << "laughing out loud";
   }else if (abbr == "TMI") {
      cout << "too much information";
   }else{
      cout << "Unknown";
   }
   
   cout << endl;

   return 0;
}