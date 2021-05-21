#include <iostream>
#include <cmath>                   // Note: Needed for math functions in part (3)
using namespace std;

int main() {
   double wallHeight = 0.0;
   double wallWidth = 0.0;
   double wallArea = 0.0;
   
   cout << "Enter wall height (feet): ";
   cin  >> wallHeight;
   cout << endl;
   
   cout << "Enter wall width (feet): ";
   cin  >> wallWidth;
   cout << endl;
   
   // Calculate and output wall area
   wallArea = wallWidth * wallHeight;
   cout << "Wall area: " << wallArea << " square feet" << endl;  
   
   // FIXME (2): Calculate and output the amount of paint in gallons needed to paint the wall
   const double SQ_FT_PER_GAL = 350;
   
   double totalPaint = wallArea / SQ_FT_PER_GAL;
   
   cout << "Paint needed: " << totalPaint << " gallons" <<endl;
   cout << "Cans needed: " << ceil(totalPaint) << " can(s)" << endl;

   // FIXME (3): Calculate and output the number of 1 gallon cans needed to paint the wall, rounded up to nearest integer

   return 0;
}