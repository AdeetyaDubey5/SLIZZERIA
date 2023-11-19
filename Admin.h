#ifndef ADMIN_H
#define ADMIN_H

#include "MenuItem.h"
#include <string>
#include <list>

class Admin {
public:
    void adminLogin();
    void addItem(string itemName, double itemPrice);
    void displayMenu() const;
    void deleteItem(const string& itemName);
    void updateItem(const string& itemName, double newPrice);
    const MenuItem* findItemByName(const string& itemName) const;

private:
    std::list<MenuItem> menu; 
};

#endif // ADMIN_H
