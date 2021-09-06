#include <iostream>
#include "ItemToPurchase.h"
using namespace std;

#include "ItemToPurchase.h"
ItemToPurchase::ItemToPurchase() {
  itemName = "none";
  itemPrice = 0.0;
  itemQuantity = 0;
}

//Name
void ItemToPurchase::SetName(string newName) {
  itemName = newName;
  return;
}

string ItemToPurchase::GetName() {
  return itemName;
}

//Price
void ItemToPurchase::SetPrice(double newPrice) {
  itemPrice = newPrice;
  return;
}

double ItemToPurchase::GetPrice() {
  return itemPrice;
}

//Quantity
void ItemToPurchase::SetQuantity(int newQuantity) {
  itemQuantity = newQuantity;
  return;
}

int ItemToPurchase::GetQuantity() {
  return itemQuantity;
}

//Utility Methods
void ItemToPurchase::PrintItem() {
  cout << "Name:     " << itemName << endl;
  cout << "Price:    " << itemPrice << endl;
  cout << "Quantity: " << itemQuantity << endl;
  return;
}

double ItemToPurchase::GetTotalPrice() {
  return itemPrice * itemQuantity;
}