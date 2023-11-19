#include "Admin.h"
#include <iostream>

using namespace std;

void Admin::adminLogin() {
    
}

void Admin::addItem(string itemName, double itemPrice) {
    menu.push_back(MenuItem(itemName, itemPrice));
    cout << itemName << " added to the menu." << endl;
}

void Admin::displayMenu() const {
    if (menu.empty()) {
        cout << "Menu is empty." << endl;
    } else {
        cout << "Menu Items:" << endl;
        for (const MenuItem& item : menu) {
            cout << item.name << " - rs." << item.price << endl;
        }
    }
}

void Admin::deleteItem(const string& itemName) {
    auto it = menu.begin();
    while (it != menu.end()) {
        if (it->name == itemName) {
            it = menu.erase(it);
            cout << itemName << " removed from the menu." << endl;
            return;
        } else {
            ++it;
        }
    }
    cout << itemName << " not found in the menu." << endl;
}

void Admin::updateItem(const string& itemName, double newPrice) {
    for (MenuItem& item : menu) {
        if (item.name == itemName) {
            item.price = newPrice;
            cout << "Price of " << itemName << " updated to rs." << newPrice << endl;
            return;
        }
    }
    cout << itemName << " not found in the menu." << endl;
}

const MenuItem* Admin::findItemByName(const string& itemName) const {
    for (const MenuItem& item : menu) {
        if (item.name == itemName) {
            return &item;
        }
    }
    return nullptr; 
}
