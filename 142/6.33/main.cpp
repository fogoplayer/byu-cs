#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int DIMENSION = 10;
const int NUM_ROWS = DIMENSION;
const int NUM_COLS = DIMENSION;

void InitializeArray(double newArray[][10]);
void PrintArray(double hotPlate[][10]);
double IterateNewTemp(double hotPlate[][10]);
void OutputArray(double hotPlate[][10]);
void InitializeArrayFromFile(double newArray[][10]);

int main() {
  double hotPlate[NUM_ROWS][NUM_COLS];

  cout << "Hotplate simulator" << endl << endl;

  //Initialize
  InitializeArray(hotPlate);
  cout << "Printing the initial plate values..." << endl;
  PrintArray(hotPlate);

  //First iteration
  double maxTempChange = IterateNewTemp(hotPlate);
  cout << "Printing plate after one iteration..." << endl;
  PrintArray(hotPlate);
  
  //Other iterations
  do{
    maxTempChange = IterateNewTemp(hotPlate);
  } while(maxTempChange > 0.1);

  //Final plate
  cout << "Printing final plate..." << endl;
  PrintArray(hotPlate);

  //file output
  cout << "Writing final plate to \"Hotplate.csv\"..." << endl << endl;
  OutputArray(hotPlate);

  //File input
  int i = 0;
  const int TIMES_TO_ITERATE = 3;
  InitializeArrayFromFile(hotPlate);
  for(i = 0; i < TIMES_TO_ITERATE; ++i){
    IterateNewTemp(hotPlate);
  }
  cout << "Printing input plate after 3 updates..." << endl;
  PrintArray(hotPlate);
}

void InitializeArray(double newArray[][10]) {
  int i;
  int j;
  //i = rows; j = columns
  for(i = 0; i < NUM_ROWS; ++i) {
    for(j = 0; j < NUM_COLS; ++j) {
      if( (i == 0 || i == NUM_ROWS - 1) && (j > 0 && j < NUM_COLS - 1) ) {
        newArray[i][j] = 100.00;
      }
      else {
        newArray[i][j] = 0.00;
      }
    }
  }
}

void PrintArray(double hotPlate[][10]){
  int i;
  int j;
  //i = rows; j = columns
  for(i = 0; i < NUM_ROWS; ++i) {
    for(j = 0; j < NUM_COLS; ++j) {
      cout << fixed << setprecision(3) << setw(9) << hotPlate[i][j];
      if(j< NUM_COLS - 1){
        cout << ",";
      }
    }
    cout << endl;
  }
  cout << endl;
}

double IterateNewTemp(double hotPlate[][10]) {
  double newArray[NUM_ROWS][NUM_COLS];
  int i;
  int j;
  double maxTempChange = 0.0;

  //Make a copy of hotPlate
  for(i = 0; i < NUM_ROWS; ++i) {
    for(j = 0; j < NUM_COLS; ++j) {
      newArray[i][j] = hotPlate[i][j];
    }
  }

  for(i = 0; i < NUM_ROWS; ++i) {
    for(j = 0; j < NUM_COLS; ++j) {
      //not border position
      if( (i > 0 && i < NUM_ROWS - 1) && (j > 0 && j < NUM_COLS - 1) ) {
        hotPlate[i][j] = (newArray[i-1][j] + newArray[i+1][j] + newArray[i][j-1] + newArray[i][j+1]) / 4;
        double tempDifference = hotPlate[i][j] - newArray[i][j];
        if (tempDifference > maxTempChange){
          maxTempChange = tempDifference;
        }
      }
    }
  }

  return maxTempChange;
}

void OutputArray(double hotPlate[][10]) {
  int i;
  int j;

  ofstream output;
  output.open("Hotplate.csv");
  if(output.is_open()) {
    //i = rows; j = columns
    for(i = 0; i < NUM_ROWS; ++i) {
      for(j = 0; j < NUM_COLS; ++j) {
        output << fixed << setprecision(3) << setw(9) << hotPlate[i][j];
        if(j< NUM_COLS - 1){
          output << ",";
        }
      }
      output << endl;
    }
    output << endl;
  }
  output.close(); 
}

void InitializeArrayFromFile(double newArray[][10]) {
  ifstream input;
  input.open("Inputplate.txt");

  if(input.is_open()) {
    int i;
    int j;
    //i = rows; j = columns
    for(i = 0; i < NUM_ROWS; ++i) {
      for(j = 0; j < NUM_COLS; ++j) {
        input >> newArray[i][j];
      }
    }
    input.close();
  }
}