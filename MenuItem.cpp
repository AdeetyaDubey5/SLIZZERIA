#include "MenuItem.h"
using namespace std;

MenuItem::MenuItem(string itemName, double itemPrice)
    : name(itemName), price(itemPrice), next(nullptr) {}
