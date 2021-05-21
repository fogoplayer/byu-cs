#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H
#include <string>
using namespace std;

class ItemToPurchase {
  public:
    // ItemToPurchase();
    ItemToPurchase(string name = "none", string description = "none", double price = 0, int quantity = 0);

    void SetName(string newName);
    string GetName();

    void SetDescription(string newDescription);
    string GetDescription();
    
    void SetPrice(double newPrice);
    double GetPrice();

    void SetQuantity(int newQuantity);
    int GetQuantity();

    void PrintItemCost();
    void PrintItemDescription();
    
    double GetTotalPrice();

  private:
    string itemName;
    double itemPrice;
    int itemQuantity;
    string itemDescription;
};

#endif