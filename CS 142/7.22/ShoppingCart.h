#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H
#include <string>
#include <vector>
#include "ItemToPurchase.h"
using namespace std;

class ShoppingCart {
  public:
    ShoppingCart(string newName = "none", string date = "January 1, 2016");

    string GetCustomerName();
    string GetCartCreationDate();

    void addItemToCart(ItemToPurchase newItem);
    void removeItemFromCart(string itemName);
    void updateItemQuantity(string itemName, int newQuantity);
    int GetTotalItemQuantity();
    double GetTotalItemCost();
    void PrintAllDescriptions();
    void PrintAllItemsAndTotal();


  private:
    string customerName;
    string cartCreationDate;
    vector<ItemToPurchase> itemsVector;
    int GetItemIndexFromName(string itemName);
};
#endif