#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>

using namespace std;

class MenuItem {
public:
    string name;
    double price;
    MenuItem* next;

    MenuItem(string itemName, double itemPrice);
};

#endif



