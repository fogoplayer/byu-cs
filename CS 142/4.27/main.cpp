#include <iostream>
#include <string>
using namespace std;

//Input functions
string PrintPromptAndGetResponse(string prompt, bool YesOrNoQuestion);
string ValidateResponse(string userResponse, bool yesOrNoQuestion);

//Question functions
void CheckColor();
void SpecifyShadeOfBrown();
void IsItServedWithCheese();
void IsItStarchy();
void DoesItHaveSaltOnIt();

//Outcome functions
void ItsAPotato();
void ItsNotAPotato();
void ItsAFrenchFry();
void ItsAFileFolder();

/*--------------------------------------------------------Main--------------------------------------------------------*/
int main() {
   cout << "I hear you have an object that you suspect is a potato. Let's find out." << endl;
   cout << "(Please put in all answers in lowercase.)\n" << endl;
   CheckColor();  //The first question of the chain; all other questions are a part of this stack

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
      //If the response is "yes" or a "no", send it back
      if ( (userResponse == ("yes")) || (userResponse == "no") ) {
         return userResponse;
      }
      //If the answer is something OTHER than yes or no, ask them to try again, validate it, and send it back
      else {
         userResponse = PrintPromptAndGetResponse("That's an invalid response. Please try again.", true);
         userResponse = ValidateResponse(userResponse, true);
         return userResponse;
      }
   }
   //If it's not a yes or no question, edge cases are handled in the questions' logic and the response doesn't need to
   //    be validated
   else {
      return userResponse;
   }
}

/*-------------------------------------------------Question functions-------------------------------------------------*/
void CheckColor() {
   string userResponse = PrintPromptAndGetResponse("What color is it? (Input a string)");
   if (userResponse.find("brown") != string::npos) {  //using string.find() allows for more open-ended responses like
                                                        //  "kinda brown" or "grayish-white"
      SpecifyShadeOfBrown();
   }else if (userResponse.find("white") != string::npos) {
      IsItStarchy();
   }else{
      ItsNotAPotato();
   }
}

//Each question function prompts the user, gets a response, and calls one of two functions based on the response
void SpecifyShadeOfBrown() {
   string userResponse = PrintPromptAndGetResponse("Is it dark brown? (yes or no)",true);
   if (userResponse == "yes") {
      IsItServedWithCheese();
   }
   else {
      DoesItHaveSaltOnIt();
   }

}

void IsItServedWithCheese() {
   string userResponse = PrintPromptAndGetResponse("Is it served with cheese? (yes or no)", true);
   if (userResponse == "yes") {
      ItsAPotato();
   }
   else {
      ItsNotAPotato();
   }
}

void IsItStarchy() {
   string userResponse = PrintPromptAndGetResponse("Is it starchy? (yes or no)", true);
   if (userResponse == "yes") {
      IsItServedWithCheese();
   }
   else {
      ItsNotAPotato();
   }
}

void DoesItHaveSaltOnIt() {
   string userResponse = PrintPromptAndGetResponse("Does it have salt on it? (yes or no)", true);
   if (userResponse == "yes") {
      ItsAFrenchFry();
   }
   else {
      ItsAFileFolder();
   }
}

/*-------------------------------------------------Outcome functions--------------------------------------------------*/
void ItsAPotato() {
   cout << "It's probably a potato!" << endl;
}

void ItsNotAPotato() {
   cout << "It's probably not a potato" << endl;
}

void ItsAFrenchFry() {
   cout << "You seem to have found a French fry. Which is, deep down, a potato." << endl;
}

void ItsAFileFolder() {
   cout << "That's probably a file folder. Or maybe a pair of khakis." << endl;
}