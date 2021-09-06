#include <iostream>
#include <string>
#include "ShoppingCart.h"
#include "ItemToPurchase.h"


ShoppingCart::ShoppingCart(string newName, string date) {
  customerName = newName;
  cartCreationDate = date;
  return;
}


string ShoppingCart::GetCustomerName() {
  return customerName;
}

string ShoppingCart::GetCartCreationDate() {
  return cartCreationDate;
}


void ShoppingCart::addItemToCart(ItemToPurchase newItem) {
  if(GetItemIndexFromName(newItem.GetName()) == -1){
    itemsVector.push_back(newItem);
  }
  else {
    cout << "Item is already found in the cart. It will not be added." << endl;
  }
  return;
}

void ShoppingCart::removeItemFromCart(string itemName) {
  int i = ShoppingCart::GetItemIndexFromName(itemName);
  if(i >= 0) {
    itemsVector.erase(itemsVector.begin() + i);
  }
  else {
    cout << "Item not found in cart. It will not be removed." << endl;
  }
  return;
}

void ShoppingCart::updateItemQuantity(string itemName, int newQuantity) {
  int i = ShoppingCart::GetItemIndexFromName(itemName);
  if(i >= 0) {
    itemsVector[i].SetQuantity(newQuantity);
  }
  else {
    cout << "Item not found in cart. It will not be modified." << endl;
  }
  return;
}

int ShoppingCart::GetTotalItemQuantity() {
  int quantityTotal = 0;
  for(unsigned int i = 0; i < itemsVector.size(); ++i) {
    quantityTotal += itemsVector[i].GetQuantity();
  }
  return quantityTotal;
}

double ShoppingCart::GetTotalItemCost() {
  double totalItemCost = 0.0;
  for(unsigned int i = 0; i < itemsVector.size(); ++i) {
    totalItemCost += itemsVector[i].GetTotalPrice();
  }

  return totalItemCost;
}

void ShoppingCart::PrintAllDescriptions() {
  cout << customerName << "'s Shopping Cart - " << cartCreationDate << endl;

  if(itemsVector.size() > 0) {
    cout << "Item Descriptions" << endl;
    for(unsigned int i = 0; i < itemsVector.size(); ++i) {
      itemsVector[i].PrintItemDescription();
    }
  }
  else {
    cout << "Shopping cart is empty." << endl;
  }
  return;
}

void ShoppingCart::PrintAllItemsAndTotal() {
  cout << customerName << "'s Shopping Cart - " << cartCreationDate << endl;
  if(itemsVector.size() > 0) {
    cout << "Number of Items: " << GetTotalItemQuantity() << endl << endl;

    for(unsigned int i = 0; i < itemsVector.size(); ++i) {
      itemsVector[i].PrintItemCost();
    }

    cout << "Total: $" << GetTotalItemCost() << endl;
  }
  else {
    cout << "Shopping cart is empty." << endl;
  }
  return;
}


int ShoppingCart::GetItemIndexFromName(string itemName) {
  for(unsigned int i = 0; i < itemsVector.size(); ++i) {
    if(itemsVector[i].GetName() == itemName) {
      return i;
    }
  }
  return -1;
}
