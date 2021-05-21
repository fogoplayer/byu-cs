#include <iostream>
#include <math.h>
using namespace std;

//Function declarations
void numPizzasNeeded(int numGuests, int& numLargePizzas, int& numMediumPizzas, int& numSmallPizzas);
double calcTotalPizzaArea(int numLargePizzas, int numMediumPizzas, int numSmallPizzas);
double areaOfAPizza(double diameter);
int calcTotalCost(int tip, int numLargePizzas, int numMediumPizzas, int numSmallPizzas);

int main() {
   //Initialize Variables
   int numGuests = 0;
   // int tip = 0;
   int numLargePizzas = 0;
   int numMediumPizzas = 0;
   int numSmallPizzas = 0;
   
   //Part 1 - Count your Many Pizzas
   cout << "Please enter how many guests to order for: ";
   cin >> numGuests;
   cout << endl;
   
   numPizzasNeeded(numGuests, numLargePizzas, numMediumPizzas, numSmallPizzas);
   cout << numLargePizzas << " large pizzas, " << numMediumPizzas << " medium pizzas, and "
         << numSmallPizzas << " small pizzas will be needed." << endl << endl;
      
   //Part 2 - Serving Size
   double totalPizzaArea = calcTotalPizzaArea(numLargePizzas, numMediumPizzas, numSmallPizzas);
   double pizzaPerGuest = totalPizzaArea / numGuests;
   cout << "A total of " << totalPizzaArea << " square inches of pizza will be ordered (" << pizzaPerGuest << " per guest)."
         << endl << endl;
   
   //Part 3 - Supplementing the Budget
   cout << "Please enter the tip as a percentage (i.e. 10 means 10%): ";
   int tipPercentage;
   cin >> tipPercentage;
   cout << endl;
   double totalCost = calcTotalCost(tipPercentage, numLargePizzas, numMediumPizzas, numSmallPizzas);
   cout << "The total cost of the event will be: $" << totalCost << endl;
   
   return 0;
}

void numPizzasNeeded(int numGuests, int& numLargePizzas, int& numMediumPizzas, int& numSmallPizzas){
   const int GUESTS_PER_LARGE_PIZZA = 7;
   const int GUESTS_PER_MEDIUM_PIZZA = 3;
   const int GUESTS_PER_SMALL_PIZZA = 1;
   
   numLargePizzas = numGuests / GUESTS_PER_LARGE_PIZZA;     //Divide the number of guests by the number of people fed per pizza
   numGuests %= GUESTS_PER_LARGE_PIZZA;                     //Use modulo to figure out how many guests remain unfed
   numMediumPizzas = numGuests / GUESTS_PER_MEDIUM_PIZZA;   //Repeat for smaller pizza sizes
   numGuests %= GUESTS_PER_MEDIUM_PIZZA;
   numSmallPizzas = numGuests / GUESTS_PER_SMALL_PIZZA;
   return;
}

double calcTotalPizzaArea(int numLargePizzas, int numMediumPizzas, int numSmallPizzas){
   const double LARGE_PIZZA_DIAMETER = 20.0;
   const double MEDIUM_PIZZA_DIAMETER = 16.0;
   const double SMALL_PIZZA_DIAMETER = 12.0;
   
   //Multiply the number of each pizza by the size
   double totalPizzaArea = numLargePizzas * areaOfAPizza(LARGE_PIZZA_DIAMETER)
         + numMediumPizzas * areaOfAPizza(MEDIUM_PIZZA_DIAMETER)
         + numSmallPizzas * areaOfAPizza(SMALL_PIZZA_DIAMETER);
   return totalPizzaArea;
}

double areaOfAPizza(double diameter){
   const double PI = 3.14159265;
   const double R = diameter / 2;
   
   double area = PI * pow(R, 2);
   return area;
}

int calcTotalCost(int tip, int numLargePizzas, int numMediumPizzas, int numSmallPizzas){
   const double LARGE_PIZZA_COST = 14.68;
   const double MEDIUM_PIZZA_COST = 11.48;
   const double SMALL_PIZZA_COST = 7.28;
   
   //Determine JUST the cost of the pizzas (no tip)
   double subtotal = numLargePizzas * LARGE_PIZZA_COST + numMediumPizzas * MEDIUM_PIZZA_COST + numSmallPizzas * SMALL_PIZZA_COST;
   int totalCost = round(subtotal + subtotal * (tip / 100.0));  //cost of the pizzas + tip amount
   return totalCost;
}