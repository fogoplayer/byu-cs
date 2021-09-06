#include <iostream>
using namespace std;

int main() {
   int arrowBaseHeight = 0;
   int arrowBaseWidth = 0;
   int arrowHeadWidth = 0;
   
   cout << "Enter arrow base height: " << endl;
   cin >> arrowBaseHeight;
   
   cout << "Enter arrow base width: " << endl;
   cin >> arrowBaseWidth;
   do{
      cout << "Enter arrow head width: " << endl;
      cin >> arrowHeadWidth;
   }while (arrowHeadWidth <= arrowBaseWidth);   //If the head is smaller or equal to the base, get a new input
   
   // Draw arrow base
   for (int i = 1; i <= arrowBaseHeight; ++i){
      for (int j = 1; j <= arrowBaseWidth; ++j) {
         cout << "*";
      }
      cout << endl;
   }
    
   // Draw arrow head (width = 4)
   for (int i = arrowHeadWidth; i >= 1; --i){   //Start at the arrowhead width and count down 
      for (int j = i; j >= 1; --j) {   //Because i gets smaller, it tells you the number of *s in a row
         cout << "*";
      }
      cout << endl;
   }
   
   return 0;
}