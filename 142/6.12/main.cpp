#include <iostream>
#include <vector>
using namespace std;

void PrintTotalWeight(const vector<double> weights){
   double totalWeight = 0;
   for(unsigned int i = 0; i < weights.size(); ++i) {
      totalWeight += weights[i];
   }
   cout << "Total weight: " << totalWeight << endl;
}

void PrintAvgWeight(const vector<double> weights){
   double totalWeight = 0;
   for(unsigned int i = 0; i < weights.size(); ++i) {
      totalWeight += weights[i];
   }
   cout << "Average weight: " << totalWeight / weights.size() << endl;
}

void PrintMaxWeight(const vector<double> weights){
   double maxWeight = weights[0];
   for(unsigned int i = 0; i < weights.size(); ++i) {
      maxWeight = weights[i] > maxWeight ? weights[i] : maxWeight;
   }
   cout << "Max weight: " << maxWeight << endl;
}

int main() {
   
   /* Type your code here. */
   //Get inputs
   const int VAL_COUNT = 5;
   vector<double> weights(VAL_COUNT);
   for(unsigned i = 1; i <= weights.size(); ++i){
      cout << "Enter weight " << i << ": ";
      cin >> weights[i - 1];
      cout << endl;
   }
   
   //Print inputs
   cout << endl << "You entered: ";
   for(unsigned i = 0; i < weights.size(); ++i){
      cout << weights[i] << " ";
   }
   cout << endl;
   
   //Print total/avg/max weight
   PrintTotalWeight(weights);
   PrintAvgWeight(weights);
   PrintMaxWeight(weights);

   return 0;
}