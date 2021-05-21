#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//place function prototypes here...
double CalcRectanglePerimeter(double height, double width);
void PrintRectanglePerimeter(double height, double width);
void DoubleRectanglePerimeter(double& height, double& width);
double CalcCircumferenceOfCircle(double radius);
double CalcAreaOfCircle(double radius);
double CalcVolumeOfSphere(double radius);
void Swap(int& val1, int& val2);
void Swap(double& val1, double& val2);

//Global consts
const double PI = 3.14;

//main function
int main(){
   cout << "Getting this line to print earns you points!\n";

   double height = 0;
   double width = 0;
   double radius = 0;

   cin >> height >> width >> radius;

   PrintRectanglePerimeter(height, width);
   cout << CalcRectanglePerimeter(height, width) << std::endl;
   cout << "... about to double height and width...\n";
   DoubleRectanglePerimeter(height, width);
   PrintRectanglePerimeter(height, width);

   return 0;
}

double CalcRectanglePerimeter(double height, double width){
   return ((2 * height) + (2 * width));
}

void PrintRectanglePerimeter(double height, double width){
   cout << "A rectangle with height " << fixed << setprecision(1) << height
        << " and width " << fixed << setprecision(1) << width
        << " has a perimeter of " << fixed << setprecision(1) << CalcRectanglePerimeter(height,width)
        << "." << endl;
}

void DoubleRectanglePerimeter(double& height, double& width){
   height *= 2;
   width *= 2;
}

double CalcCircumferenceOfCircle(double radius){
   return 2 * PI * radius;
}

double CalcAreaOfCircle(double radius){
   return PI * pow(radius, 2);
}

double CalcVolumeOfSphere(double radius){
   return 4.0 / 3.0 * PI * pow(radius, 3);
}

void Swap(int& val1, int& val2){
   int tempVal1 = val1;
   val1 = val2;
   val2 = tempVal1;
}

void Swap(double& val1, double& val2){
   double tempVal1 = val1;
   val1 = val2;
   val2 = tempVal1;
}
