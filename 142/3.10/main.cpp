#include <iostream>
#include <iomanip>
using namespace std;

//Write your functions here
double CalcRectanglePerimeter(double height, double width){
   return 2 * height + 2 * width;
}

void PrintRectanglePerimeter(double height, double width){
   cout << "A rectangle with height " << fixed << setprecision(1) << height 
         << " and width " << fixed << setprecision(1) << width
         << " has a perimeter of " << fixed << setprecision(1) << CalcRectanglePerimeter(height,width)
         << ".";
}

void DoubleRectanglePerimeter(double& height, double& width){
   height *= 2;
   width *= 2;
}

int main() {
   
   /*
     You are free to write code here to test your functions, but you are not required to do so.
     Our unit tests utilize their own main() function and are able to ignore this one...
   */
   double height;
   double width;
   
   cin >> height;
   cin >> width;
   PrintRectanglePerimeter(height, width);
   
   
   return 0;
}