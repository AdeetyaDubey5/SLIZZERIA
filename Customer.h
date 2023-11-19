#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "MenuItem.h"  
#include <list>
#include <string>

class Customer {
    // private:
    // std::vector<std::string> order;

public:
    //std::vector<std::string> order;
    void addToOrder(const MenuItem& item);
    void removeFromOrder(const std::string& itemName);
    void viewOrder() const;
    void clearOrder();

    /// @brief 
    /// @param username 
    /// @param existingUsernames 
    /// @return 
    bool isUsernameTaken(const std::string& username, const std::vector<std::string>& existingUsernames) const;
    bool checkPassword(const std::string& password) const;

private:
    list<MenuItem> order; 
};

#endif

