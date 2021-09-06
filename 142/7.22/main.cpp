//A Note regarding 'using namespace std':
// The author of this code prefers to not have the line 'using namespace std;'
// Instead, you will see 'std::' in front of string, cout, and other identifiers
// You could put 'using namespace std;' at the top of your code and not need 'std::' in front of these words,
// but many people consider it better practice to not have 'using namespace std;'

#include <iostream>
#include <string>
#include "ItemToPurchase.h"
#include "ShoppingCart.h"

std::string GetUserString(const std::string& prompt);

void AddMenuOption(ShoppingCart& shoppingCart);
void RemoveMenuOption(ShoppingCart& shoppingCart);
void ChangeMenuOption(ShoppingCart& shoppingCart);
void DescriptionsMenuOption(ShoppingCart& shoppingCart);
void CartMenuOption(ShoppingCart& shoppingCart);
void OptionsMenuOption();
void QuitMenuOption();


int main() {
  std::string customerName = GetUserString("Enter Customer's Name: ");
  std::string todayDate = GetUserString("Enter Today's Date: ");
  ShoppingCart shoppingCart(customerName, todayDate);

  std::string userMenuChoice = "none";
  bool continueMenuLoop = true;
  while (continueMenuLoop) {
    cout << std::endl;
    userMenuChoice = GetUserString("Enter option: ");

    if (userMenuChoice == "add") {
      AddMenuOption(shoppingCart);
    }
    else if (userMenuChoice == "remove") {
      RemoveMenuOption(shoppingCart);
    }
    else if (userMenuChoice == "change") {
      ChangeMenuOption(shoppingCart);
    }
    else if (userMenuChoice == "descriptions") {
      DescriptionsMenuOption(shoppingCart);
    }
    else if (userMenuChoice == "cart") {
      CartMenuOption(shoppingCart);
    }
    else if (userMenuChoice == "options") {
      OptionsMenuOption();
    }
    else if (userMenuChoice == "quit") {
      QuitMenuOption();
      continueMenuLoop = false;
    }
    else {
      OptionsMenuOption();
    }
  }

  return 0;
}


std::string GetUserString(const std::string& prompt) {
  std::string userAnswer = "none";

  std::cout << prompt;
  std::getline(std::cin, userAnswer);
  std::cout << std::endl;
  return userAnswer;
}
double GetUserDouble(const std::string& prompt) {
  double userAnswer = 0.0;

  std::cout << prompt;
  std::cin >> userAnswer;
  std::cin.ignore();
  std::cout << std::endl;
  return userAnswer;
}
int GetUserInt(const std::string& prompt) {
  int userAnswer = 0;

  std::cout << prompt;
  std::cin >> userAnswer;
  std::cin.ignore();
  std::cout << std::endl;
  return userAnswer;
}


void AddMenuOption(ShoppingCart& shoppingCart) {
  std::string itemName = GetUserString("Enter the item name: ");
  std::string itemDescription = GetUserString("Enter the item description: ");
  double itemPrice = GetUserDouble("Enter the item price: ");
  int itemQuantity = GetUserInt("Enter the item quantity: ");

  ItemToPurchase newItem(itemName, itemDescription, itemPrice, itemQuantity);
  shoppingCart.addItemToCart(newItem);
}

void RemoveMenuOption(ShoppingCart& shoppingCart) {
  std::string nameOfItemToRemove = GetUserString("Enter name of the item to remove: ");
  
  shoppingCart.removeItemFromCart(nameOfItemToRemove);
}

void ChangeMenuOption(ShoppingCart& shoppingCart) {
  std::string nameOfItemToChange = GetUserString("Enter the item name: ");
  int newItemQuantity = GetUserInt("Enter the new quantity: ");

  shoppingCart.updateItemQuantity(nameOfItemToChange, newItemQuantity);
}

void DescriptionsMenuOption(ShoppingCart& shoppingCart) {
  shoppingCart.PrintAllDescriptions();
}

void CartMenuOption(ShoppingCart& shoppingCart) {
  shoppingCart.PrintAllItemsAndTotal();
}

void OptionsMenuOption() {
  std::cout << "MENU" << std::endl
            << "add - Add item to cart" << std::endl
            << "remove - Remove item from cart" << std::endl
            << "change - Change item quantity" << std::endl
            << "descriptions - Print the items' descriptions" << std::endl
            << "cart - Print the shopping cart" << std::endl
            << "options - Print the options menu" << std::endl
            << "quit - Quit" << std::endl << std::endl;
}

void QuitMenuOption() {
  std::cout << "Goodbye." << std::endl;
}