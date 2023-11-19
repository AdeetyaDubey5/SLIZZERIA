#include "Customer.h"
#include <iostream>
#include <string>

using namespace std;


MenuItem::MenuItem(string itemName, double itemPrice) : name(itemName), price(itemPrice), next(nullptr) {}

void Customer::addToOrder(const MenuItem& item) {
    
    MenuItem* newOrderItem = new MenuItem(item.name, item.price);

    
    order.push_back(*newOrderItem);

    cout << item.name << " added to the orders." << endl;
}

void Customer::removeFromOrder(const std::string& itemName) {
    
    auto it = order.begin();   
    while (it != order.end()) {
        if (it->name == itemName) {
            it = order.erase(it);
            cout << itemName << " removed from the orders." << endl;
            return;
        } else {
            ++it;
        }
    }

    cout << itemName << " not found in the orders." << endl;
}

void Customer::viewOrder() const {
    if (order.empty()) {
        cout << "Order is empty." << endl;
        return;
    }

    cout << "Current Order:" << endl;
    for (const MenuItem& item : order) {
        cout << item.name << " - $" << item.price << endl;
    }
}

void Customer::clearOrder() {
    order.clear();
    cout << "Order has been cleared." << endl;
}

bool Customer::isUsernameTaken(const std::string& username, const std::vector<std::string>& existingUsernames) const {
    return std::find(existingUsernames.begin(), existingUsernames.end(), username) != existingUsernames.end();
}

bool Customer::checkPassword(const std::string& password) const {
    // Ensure the password is at least 8 characters long
    if (password.length() < 8) {
        return false;
    }

    // Check for at least one digit, one uppercase letter, one lowercase letter, and one special character
    bool hasDigit = false;
    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasSpecialChar = false;

    for (char ch : password) {
        if (isdigit(ch)) {
            hasDigit = true;
        } else if (isupper(ch)) {
            hasUppercase = true;
        } else if (islower(ch)) {
            hasLowercase = true;
        } else if (ispunct(ch) || ch == ' ') { // Consider other characters as special characters
            hasSpecialChar = true;
        }
    }

    return hasDigit && hasUppercase && hasLowercase && hasSpecialChar;
}
