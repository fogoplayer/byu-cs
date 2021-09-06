#include <iostream>
#include <string>
using namespace std;

int main() {

   /* Type your code here. */
   string userString = "";
   
   cout << "Enter text: ";
   getline(cin, userString);
   cout << endl;
   
   cout << "You entered: " << userString << endl;
   
   if (userString.find("BFF") != string::npos){
      cout << "BFF: best friend forever" << endl;
   }
   
   if (userString.find("IDK") != string::npos) {
      cout << "IDK: I don't know" << endl;
   }
   
   if (userString.find("IMHO") != string::npos){
      cout << "IMHO: in  my humble opinion" << endl;
   }
   
   if (userString.find("LOL") != string::npos) {
      cout << "LOL: laughing out loud" << endl;
   }
   
   if (userString.find("JK") != string::npos) {
      cout << "JK: just kidding" << endl;
   }
   
   if (userString.find("TMI") != string::npos) {
      cout << "TMI: too much information" << endl;
   }
   
   if (userString.find("TTYL") != string::npos) {
      cout << "TTYL: talk to you later" << endl;
   }
   
   return 0;
}