#include <iostream>
#include <iomanip>
#include "ItemToPurchase.h"
using namespace std;

ItemToPurchase::ItemToPurchase(string name, string description, double price, int quantity) {
  itemName = name;
  itemDescription = description;
  itemPrice = price;
  itemQuantity = quantity;
}

//Name
void ItemToPurchase::SetName(string newName) {
  itemName = newName;
  return;
}

string ItemToPurchase::GetName() {
  return itemName;
}

//Description
void ItemToPurchase::SetDescription(string newDescription){
  itemDescription = newDescription;
  return;
}

string ItemToPurchase::GetDescription(){
  return itemDescription;
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

//Printing
void ItemToPurchase::PrintItemCost() {
  //[Name] [quantity] @ $[Price] = $[Total Price]
  cout << fixed << setprecision(2) << itemName << " " << itemQuantity << " @ $" << itemPrice << " = $" << itemQuantity * itemPrice << endl;
  return;
}

void ItemToPurchase::PrintItemDescription() {
  cout << itemName << ": " << itemDescription << endl;
  return;
}

//Utility Methods
double ItemToPurchase::GetTotalPrice() {
  return itemPrice * itemQuantity;
}