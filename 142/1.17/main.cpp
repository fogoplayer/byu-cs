#include <iostream>
using namespace std;

int main() {
   //cout the header, using double "endl"s to create the line breaks
   cout << "\t\t\t\t" << "Simple BYU Trivia"<< endl << endl;
   cout << "\t\t" << "Questions" << "\t\t\t\t" << "Answers" << endl << endl;
   
   //cout the questions and answers
   //Each line has different numbers of tabs due to the different question lengths
   cout << "What was the original name of BYU?"                << "\t\t"   << "Brigham Young Academy"    << endl;
   cout << "When was BYU established?"                         << "\t\t\t" << "1875"                     << endl;
   cout << "Who was the first \"permanent\" principal of BYA?" << "\t"     << "Karl G. Maeser"           << endl;
   cout << "When did BYA turn into BYU?"                       << "\t\t\t" << "1903"                     << endl;
   cout << "To what sports conference do we belong?"           << "\t\t"   << "Independent \\Football\\" << endl;
   cout << "When did BYU \"win\" the national football title?" << "\t"     << "1984"                     << endl;
   cout << "Who won the Heisman Trophy in 1990?"               << "\t\t"   << "Ty Detmer"                << endl;
   
   return 0;
}