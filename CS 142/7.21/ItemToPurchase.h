#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H
#include <string>
using namespace std;

class ItemToPurchase {
  public:
    ItemToPurchase();
    void SetName(string newName);
    string GetName();
    
    void SetPrice(double newPrice);
    double GetPrice();

    void SetQuantity(int newQuantity);
    int GetQuantity();

    void PrintItem();
    double GetTotalPrice();

  private:
    string itemName;
    double itemPrice;
    int itemQuantity;
};
#endif