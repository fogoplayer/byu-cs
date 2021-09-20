#include <iostream>
#include <string>
using namespace std;


//Global vars
const int MAX_NUM_OF_TESTS = 10;

//Input functions
string PrintPromptAndGetResponse(string prompt, bool YesOrNoQuestion);
string ValidateResponse(string userResponse, bool yesOrNoQuestion);
bool ConfirmContinue(int testResults[MAX_NUM_OF_TESTS]);
void PrintResults(int testResults[MAX_NUM_OF_TESTS]);

//Question functions
int PotatoTest();
int SpecifyShadeOfBrown();
int IsItServedWithCheese();
int IsItStarchy();
int DoesItHaveSaltOnIt();
int FlipACoin();

//Outcome functions
int ItsAPotato();
int ItsNotAPotato();
int ItsAFrenchFry();
int ItsAFileFolder();

/*--------------------------------------------------------Main--------------------------------------------------------*/
int main() {
   bool wantToContinue = false;
   int testResults[MAX_NUM_OF_TESTS];
   for (int i = 0; i < MAX_NUM_OF_TESTS; ++i) {
      testResults[i] = -1;
   }
   
   
   cout << "I hear you have an object that you suspect is a potato. Let's find out." << endl;
   cout << "(Please put in all answers in lowercase.)\n" << endl;
   
   do {
      int isItAPotato = PotatoTest();  //The first question of the chain; all other questions are a part of this stack
      
      for (int i = 0; i < MAX_NUM_OF_TESTS; ++i) {
         if(testResults[i] < 0) {        //If the array element is empty
            testResults[i] = isItAPotato; //Record the result of the most recent test
            break;                        //And exit the loop
         }
      }
      wantToContinue = ConfirmContinue(testResults);
   }
   while (wantToContinue == true);
   
   PrintResults(testResults);

   return 0;
}

/*--------------------------------------------------Input functions---------------------------------------------------*/
string PrintPromptAndGetResponse(string prompt, bool yesOrNoQuestion = false) {
   string userResponse = "";

   cout << prompt << " ";
   getline(cin, userResponse);
   cout << endl;
   userResponse = ValidateResponse(userResponse, yesOrNoQuestion);

   return userResponse;
}

string ValidateResponse(string userResponse, bool yesOrNoQuestion) {
   //If it's a yes or no question, validate the response
   if (yesOrNoQuestion == true) {
      while (userResponse != ("yes") && (userResponse != "no")) { //If it's a yes or no question AND the answer is not
                                                                  //"yes" or "no", re-prompt
         userResponse = PrintPromptAndGetResponse("That's an invalid response. Please try again.", true);
      }
   }
   //Response is returned outside of the if/else, so both y/n and open answers get returned
   return userResponse;
}

bool ConfirmContinue(int testResults[MAX_NUM_OF_TESTS]) {
   if (testResults[MAX_NUM_OF_TESTS - 1] >= 0) {   //See if the last element in the array has been populated &
                                                   //terminate if it has
      return false;
   }
   
   
   string userResponse = PrintPromptAndGetResponse("Do you have another item you would like to test?", true);
   if (userResponse == "yes") {
      return true;
   }else{
      return false;
   }
}

void PrintResults(int testResults[MAX_NUM_OF_TESTS]) {
   cout << "Final results:" << endl;
   for (int i = 0; (i < MAX_NUM_OF_TESTS) && (testResults[i] >= 0); ++i){  //Only loop inside the array bounds and
                                                                           //while there are still values
      //print if it was a potato or not
      cout << "  Item " << i + 1 << ": ";
      if (testResults[i] == 1) {
         cout << "Potato" << endl;
      }else{
         cout << "Not a potato" << endl;
      }
   }
   cout << "Please restart the program to continue testing new objects" << endl;
}

/*-------------------------------------------------Question functions-------------------------------------------------*/
int PotatoTest() {
   string userResponse = PrintPromptAndGetResponse("What color is it? (Input a string)");
   if (userResponse.find("brown") != string::npos) {  //using string.find() allows for more open-ended responses like
                                                        //  "kinda brown" or "grayish-white"
      return SpecifyShadeOfBrown();
   }else if (userResponse.find("white") != string::npos) {
      return IsItStarchy();
   }else{
      return ItsNotAPotato();
   }
}

//Each question function prompts the user, gets a response, and calls one of two functions based on the response
int SpecifyShadeOfBrown() {
   string userResponse = PrintPromptAndGetResponse("Is it dark brown? (yes or no)",true);
   if (userResponse == "yes") {
      return IsItServedWithCheese();
   }
   else {
      return DoesItHaveSaltOnIt();
   }

}

int IsItServedWithCheese() {
   string userResponse = PrintPromptAndGetResponse("Is it served with cheese? (yes or no)", true);
   if (userResponse == "yes") {
      return ItsAPotato();
   }
   else {
      return FlipACoin();
   }
}

int IsItStarchy() {
   string userResponse = PrintPromptAndGetResponse("Is it starchy? (yes or no)", true);
   if (userResponse == "yes") {
      return IsItServedWithCheese();
   }
   else {
      return ItsNotAPotato();
   }
}

int DoesItHaveSaltOnIt() {
   string userResponse = PrintPromptAndGetResponse("Does it have salt on it? (yes or no)", true);
   if (userResponse == "yes") {
      return ItsAFrenchFry();
   }
   else {
      return ItsAFileFolder();
   }
}

int FlipACoin() {
   cout << "Y'know what, that's kind of a toss-up... literally. Let's flip a coin. "
         << "If heads, it's a potato. If tails, its not." << endl << endl;
   if (rand() > 0.5) {
      cout << "Heads! "; //Output the result of the coin toss; the function call will finish the statement
      return ItsAPotato();
   }else{
      cout << "Tails! ";
      return ItsNotAPotato();
   }
}

/*-------------------------------------------------Outcome functions--------------------------------------------------*/
int ItsAPotato() {
   cout << "It's probably a potato!" << endl;
   return 1;
}

int ItsNotAPotato() {
   cout << "It's probably not a potato" << endl;
   return 0;
}

int ItsAFrenchFry() {
   cout << "You seem to have found a French fry. Which is, deep down, a potato." << endl;
   return 0;
}

int ItsAFileFolder() {
   cout << "That's probably a file folder. Or maybe a pair of khakis." << endl;
   return 0;
}