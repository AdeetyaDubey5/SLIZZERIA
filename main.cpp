#include "Customer.h"
#include "Admin.h"
#include "MenuItem.h"
#include "Customer.cpp"
#include "Admin.cpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isUsernameTaken(const string& username, const vector<string>& existingUsernames) {
    return find(existingUsernames.begin(), existingUsernames.end(), username) != existingUsernames.end();
}

int main() {
    Admin admin;
    Customer customer;

    admin.addItem("Burger", 120);
    admin.addItem("Pizza", 240);
    admin.addItem("Pasta", 280);
    admin.addItem("Salad", 300);
    admin.addItem("Coke", 90);
    admin.addItem("Biryani", 350);
    admin.addItem("Noodles", 250);

 

    

    int userType;
    int adminChoice;
    int customerChoice;

    do {
        
        cout << "\nUser Type Selection:\n";
        cout << "1. Administrator\n";
        cout << "2. Customer\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> userType;

        switch (userType) {
            case 1:
                do {
                                   // Admin login
        string adminUsername = "admin";
        string adminPassword = "12345";

        string enteredAdminUsername;
        string enteredAdminPassword;

        cout << "Admin Login\n";
        cout << "Username: ";
        cin >> enteredAdminUsername;
        cout << "Password: ";
        cin >> enteredAdminPassword;

        if (enteredAdminUsername == adminUsername && enteredAdminPassword == adminPassword) {
             cout << "Login Successful! Welcome, Admin.\n";
        } else {
            cout << "Login Failed! Exiting program.\n";
            return 0;
    }
                    cout << "\nAdmin Menu Dashboard:\n";
                    cout << "1. Display Menu\n";
                    cout << "2. Add Item\n";
                    cout << "3. Delete Item\n";
                    cout << "4. Update Item\n";
                    cout << "5. Exit Admin Dashboard\n";
                    cout << "Enter your choice: ";
                    cin >> adminChoice;

                    switch (adminChoice) {
                        case 1:
                            admin.displayMenu();
                            break;
                        case 2: {
                            string name;
                            double price;
                            cout << "Enter the item name: ";
                            cin >> name;
                            cout << "Enter the item price: rs.";
                            cin >> price;
                            admin.addItem(name, price);
                            break;
                        }
                        case 3: {
                            string name;
                            cout << "Enter item name to delete it: ";
                            cin >> name;
                            admin.deleteItem(name);
                            break;
                        }
                        case 4: {
                            string name;
                            double price;
                            cout << "Enter item name to update: ";
                            cin >> name;
                            cout << "Enter new price: rs";
                            cin >> price;
                            admin.updateItem(name, price);
                            break;
                        }
                        case 5:
                            cout << "Exiting admin dashboard. Goodbye!\n";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                    }
                } while (adminChoice != 5);
                break;

            case 2:
                do {
                    // Customer login/signup
    string customerUsername;
    string customerPassword;

    cout << "\nCustomer Login/Signup\n";
    cout << "1. Login\n";
    cout << "2. Signup\n";
    cout << "Enter your choice: ";
    int loginOrSignupChoice;
    cin >> loginOrSignupChoice;

    vector<string> existingCustomerUsernames; // Assuming a simple list of existing usernames
    bool loginSuccessful = false;
    switch (loginOrSignupChoice) {
        case 1:
        
     

    do {
               vector<string> existingCustomerUsernames; // Assume this contains existing usernames
    string customerUsername;
    string customerPassword;

    
        cout << "Login\n";
        cout << "Username: ";
        cin >> customerUsername;
        cout << "Password: ";
        cin >> customerPassword;

        // Check if the username exists and if the password is correct
        if (isUsernameTaken(customerUsername, existingCustomerUsernames) && customer.checkPassword(customerPassword)) {
            cout << "Login Successful! Welcome, " << customerUsername << ".\n";
            loginSuccessful = true;
        } else {
            cout << "Login Failed! Invalid username or password. Please try again.\n";
        }

    } while (!loginSuccessful);

            break;

        case 2:
            cout << "Signup\n";
            cout << "Choose a username: ";
            cin >> customerUsername;

            // Check if the username is already taken
            if (isUsernameTaken(customerUsername, existingCustomerUsernames)) {
                cout << "Signup Failed! Username already taken. Exiting program.\n";
                return 0;
            }

            cout << "Choose a password: ";
            cin >> customerPassword;

            // Add the new username to the list of existing usernames
            existingCustomerUsernames.push_back(customerUsername);

            cout << "Signup Successful! Welcome, " << customerUsername << ".\n";
            break;

        default:
            cout << "Invalid choice. Exiting program.\n";
            return 0;
    }
    
                    cout << "\nCustomer Dashboard:\n";
                    cout << "1. View Menu\n";
                    cout << "2. Add to Orders\n";
                    cout << "3. View Order\n";
                    cout << "4. Remove from Order\n";
                    cout << "5. Clear Order\n";
                    cout << "6. Exit Customer Dashboard\n";
                    cout << "Enter your choice: ";
                    cin >> customerChoice;

                    switch (customerChoice) {
                        case 1:
                            admin.displayMenu();
                            break;
                        case 2: {
                            string name;
                            double price;

                            
                            cout << "Enter the item name to add it to your orders: ";
                            cin >> name;

                            
                            const MenuItem* itemToAdd = admin.findItemByName(name);

                            if (itemToAdd) {
                                customer.addToOrder(*itemToAdd);
                            } else {
                                cout << "Item not found in the menu. Please try again.\n";
                            }
                            break;
                        }
                        case 3:
                            customer.viewOrder();
                            break;
                        case 4: {
                            string name;
                            cout << "Enter the item name to remove it from your order: ";
                            cin >> name;
                            customer.removeFromOrder(name);
                            break;
                        }
                        case 5:
                            customer.clearOrder();
                            break;
                        case 6:
                            cout << "Exiting customer dashboard. Thanks for visiting SLIZZERIA, Goodbye!\n";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                    }
                } while (customerChoice != 6);
                break;

            case 3:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (userType != 3);

    return 0;
}
