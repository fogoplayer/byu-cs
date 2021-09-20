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
   
   string acronym = "BFF";
   if (userString.find(acronym) != string::npos){
      userString.replace(userString.find(acronym),acronym.size(),"best friend forever");
   }
   
   acronym = "IDK";
   if (userString.find(acronym) != string::npos) {
      userString.replace(userString.find(acronym),acronym.size(),"I don't know");
   }
   
   acronym = "IMHO";
   if (userString.find(acronym) != string::npos){
      userString.replace(userString.find(acronym),acronym.size(),"in  my humble opinion");
   }
   
   acronym = "LOL";
   if (userString.find(acronym) != string::npos) {
      userString.replace(userString.find(acronym),acronym.size(),"laughing out loud");
   }
   
   acronym = "JK";
   if (userString.find(acronym) != string::npos) {
      userString.replace(userString.find(acronym),acronym.size(),"just kidding");
   }
   
   acronym = "TMI";
   if (userString.find(acronym) != string::npos) {
      userString.replace(userString.find(acronym),acronym.size(),"too much information");
   }
   
   acronym = "TTYL";
   if (userString.find(acronym) != string::npos) {
      userString.replace(userString.find(acronym),acronym.size(),"talk to you later");
   }
   
   cout << "Expanded: " << userString << endl;
   
   return 0;
}