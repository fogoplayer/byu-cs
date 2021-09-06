#include <iostream>
#include <vector>
#include <string>
using namespace std;

void AddPlayer(vector<int>& jerseyNums, vector<int>& ratings, int playerNum = 0){
   int jerseyNum = 0;
   int rating = 0;
   string playerText = (playerNum == 0) ? "another player" : "player " + to_string(playerNum);
   
   //Jersey number
   cout << "Enter " << playerText << "'s jersey number: ";
   cin >> jerseyNum;
   cout << endl;
   jerseyNums.push_back(jerseyNum);
   
   //Rating
   cout << "Enter " << playerText << "'s rating: ";
   cin >> rating;
   cout << endl << endl;
   ratings.push_back(rating);
}

void RemovePlayer(vector<int>& jerseyNums, vector<int>& ratings){
   int jerseyToRemove = -1;
   vector<int> newJerseys(0);
   vector<int> newRatings(0);
   
   //Get Jersey to remove
   cout << "Enter a jersey number: ";
   cin >> jerseyToRemove;
   cout << endl;
   
   //Create new arrays sans the removed player
   for (unsigned int i = 0; i < jerseyNums.size(); ++i){
      if (jerseyNums[i] != jerseyToRemove) {
         newJerseys.push_back(jerseyNums[i]);
         newRatings.push_back(ratings[i]);
      }
   }
   
   //Replace the old arrays
   jerseyNums = newJerseys;
   ratings = newRatings;
}

void UpdateRating(vector<int>& jerseyNums, vector<int>& ratings){
   int jerseyNum = -1;
   int newRating = -1;
   
   //Get the player we're updating
   cout << "Enter a jersey number: ";
   cin >> jerseyNum;
   cout << endl;
   
   //Get new rating
   cout << "Enter a rating: ";
   cin >> newRating;
   cout << endl;
   
   //Find and replace in vector
   for (unsigned int i = 0; i < jerseyNums.size(); ++i){
      if (jerseyNums[i] == jerseyNum) {
         ratings[i] = newRating;
      }
   }
}

void AboveRating(vector<int>& jerseyNums, vector<int>& ratings){
   int ratingLimit;
   
   //Get rating
   cout << "Enter a rating: ";
   cin >> ratingLimit;
   cout << endl << endl;
   
   //Print everyone above it
   cout << "ABOVE " << ratingLimit;
   for (unsigned int i = 0; i < ratings.size(); ++i){
      if (ratings[i] > ratingLimit) {
         cout << "Player " << i + 1 << " -- Jersey number: " << jerseyNums[i] << ", Rating: " << ratings[i];
      }
   }
}

void PrintRoster(vector<int>& jerseyNums, vector<int>& ratings){
   //Loop through vectors and print
   cout << "ROSTER" << endl;
   for (unsigned int i = 0; i < jerseyNums.size(); ++i){
      cout << "Player " << i + 1 << "-- Jersey number: " << jerseyNums[i] << ", Rating: " << ratings[i] << endl;
   }
}

void Menu(vector<int>& jerseyNums, vector<int>& ratings) {
   char userChoice = 'z';
   
   cout << "\nMENU\n" <<
      "a - Add player\n" <<
      "d - Remove player\n" <<
      "u - Update player rating\n" <<
      "r - Output players above a rating\n" <<
      "o - Output roster\n" <<
      "q - Quit\n" <<
      "\n" <<
      "Choose an option: ";
      cin >> userChoice;
      cout << endl << endl;
      
      switch(userChoice){
         case 'a':
            AddPlayer(jerseyNums, ratings);
            break;
            
         case 'd':
            RemovePlayer(jerseyNums, ratings);
            break;
            
         case 'u':
            UpdateRating(jerseyNums, ratings);
            break;
            
         case 'r':
            AboveRating(jerseyNums, ratings);
            break;
            
         case 'o':
            PrintRoster(jerseyNums, ratings);
            break;
            
         case 'q':
            // cout << "quit" << endl;
            exit(0);
            break;
         
         default:
            cout << "Invalid" << endl;
            break;
      }
}

int main() {
   const int INITIAL_ROSTER_SIZE = 5;
   vector<int> jerseyNums(0);
   vector<int> ratings(0);
   
   //Add first 5 players
   for(unsigned int i = 0; i < INITIAL_ROSTER_SIZE; ++i){
      AddPlayer(jerseyNums, ratings, i + 1);
   }
   cout<< endl;
   
   //Print roster
   PrintRoster(jerseyNums, ratings);
   
   //Show menu until user quits
   while (true){
      Menu(jerseyNums, ratings);
   }

   return 0;
}