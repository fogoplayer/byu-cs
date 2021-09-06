#include <iostream>
#include <iomanip>
#include "ItemToPurchase.h"
using namespace std;

int main() {
  ItemToPurchase item1;
  ItemToPurchase item2;
  string tempItemName = "No Name";
  double tempItemPrice = -9.99;
  int tempItemQuantity = -999;


  //Item 1
  cout << "Item 1" << endl;
  cout << "Enter the item name: ";
  getline(cin,tempItemName);
  item1.SetName(tempItemName);
  cout << endl << "Enter the item price: ";
  cin >> tempItemPrice;
  cin.ignore();
  item1.SetPrice(tempItemPrice);
  cout << endl << "Enter the item quantity: ";
  cin >> tempItemQuantity;
  cin.ignore();
  item1.SetQuantity(tempItemQuantity);
  cout << endl;

  //Item 2
  cout << "Item 2" << endl;
  cout << endl << "Enter the item name: ";
  getline(cin,tempItemName);
  item2.SetName(tempItemName);
  cout << endl << "Enter the item price: ";
  cin >> tempItemPrice;
  cin.ignore();
  item2.SetPrice(tempItemPrice);
  cout << endl << "Enter the item quantity: ";
  cin >> tempItemQuantity;
  cin.ignore();
  item2.SetQuantity(tempItemQuantity);
  cout << endl << endl;

  cout << "TOTAL COST" << endl;
  // [Name] [quantity] @ $[Price] = $Total Price[]
  cout << fixed << setprecision(2) << item1.GetName() << " " << item1.GetQuantity() << " @ $" << item1.GetPrice() << " = $" << item1.GetTotalPrice() << endl;
  cout << item2.GetName() << " " << item2.GetQuantity() << " @ $" << item2.GetPrice() << " = $" << item2.GetTotalPrice() << endl;
  cout << "Total: $" << item1.GetTotalPrice() + item2.GetTotalPrice();
}