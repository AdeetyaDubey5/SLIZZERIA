#ifndef ADMIN_H
#define ADMIN_H

#include "MenuItem.h"
#include <string>
#include <list>

class Admin {
public:
    void adminLogin();
    void addItem(std::string itemName, double itemPrice);
    void displayMenu() const;
    void deleteItem(const std::string& itemName);
    void updateItem(const std::string& itemName, double newPrice);
    const MenuItem* findItemByName(const std::string& itemName) const;
    void loadMenuFromFile();        // Updated Func
    void saveMenuToFile() const;    // Updated func

private:
    std::list<MenuItem> menu;
};

#endif // ADMIN_H
