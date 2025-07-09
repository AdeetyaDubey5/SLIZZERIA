#include "Customer.h"
#include "Admin.h"
#include "MenuItem.h"
#include "Customer.cpp"
#include "Admin.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <termios.h>
#include <unistd.h>
using namespace std;

bool isUsernameTaken(const string& username, const vector<string>& existingUsernames) {
    return find(existingUsernames.begin(), existingUsernames.end(), username) != existingUsernames.end();
}

string getHiddenInput() {
    string password;
    termios oldt, newt;

    // Turn echoing off
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    getline(std::cin, password);

    // Restore echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    cout << std::endl;
    return password;
}

int main() {
    Admin admin;
    admin.loadMenuFromFile();
    Customer customer;

    int userType, adminChoice, customerChoice;

    do {
        cout << "\nUser Type Selection:\n";
        cout << "1. Administrator\n";
        cout << "2. Customer\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> userType;

        switch (userType) {
            case 1: {
                // Admin login once
                    string storedUsername, storedPassword;
                    ifstream adminFile("admin.txt");
                    if (adminFile) {
                        adminFile >> storedUsername >> storedPassword;
                        adminFile.close();
                    } else {
                        cout << "Error: admin.txt not found.\n";
                        return 1;
                    }

                    string inputUsername, inputPassword;
                    cout << "Admin Login\nUsername: ";
                    cin >> inputUsername;
                    cin.ignore();
                    cout << "Password: ";
                    inputPassword = getHiddenInput();


                    if (inputUsername == storedUsername && inputPassword == storedPassword) {
                        cout << "Login Successful! Welcome, Admin.\n";

                        // Now show admin menu loop
                        do {
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
                                    cout << "Enter item name: ";
                                    cin >> name;
                                    cout << "Enter item price: Rs.";
                                    cin >> price;
                                    admin.addItem(name, price);
                                    break;
                                }
                                case 3: {
                                    string name;
                                    cout << "Enter item name to delete: ";
                                    cin >> name;
                                    admin.deleteItem(name);
                                    break;
                                }
                                case 4: {
                                    string name;
                                    double price;
                                    cout << "Enter item name to update: ";
                                    cin >> name;
                                    cout << "Enter new price: Rs.";
                                    cin >> price;
                                    admin.updateItem(name, price);
                                    break;
                                }
                                case 5:
                                    cout << "Exiting Admin Dashboard.\n";
                                    break;
                                default:
                                    cout << "Invalid choice.\n";
                            }
                        } while (adminChoice != 5);
                    } else {
                        cout << "Login Failed! Invalid credentials.\n";
                        return 0;
                    }
                break;
            }

            case 2: {
                static vector<string> existingCustomerUsernames;
                string customerUsername, customerPassword;
                bool loginSuccessful = false;
                
                cout << "\nCustomer Login/Signup\n";
                cout << "1. Login\n";
                cout << "2. Signup\n";
                cout << "Enter your choice: ";
                int loginOrSignupChoice;
                cin >> loginOrSignupChoice;

                switch (loginOrSignupChoice) {
                    case 1:
                        do {
                            cout << "Login\n";
                            cout << "Username: ";
                            cin >> customerUsername;
                            cout << "Password: ";
                            cin >> customerPassword;

                            if (isUsernameTaken(customerUsername, existingCustomerUsernames) &&
                                customer.checkPassword(customerPassword)) {
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

                        if (isUsernameTaken(customerUsername, existingCustomerUsernames)) {
                            cout << "Signup Failed! Username already taken. Exiting program.\n";
                            return 0;
                        }

                        cout << "Choose a password: ";
                        cin >> customerPassword;

                        existingCustomerUsernames.push_back(customerUsername);
                        cout << "Signup Successful! Welcome, " << customerUsername << ".\n";
                        break;

                    default:
                        cout << "Invalid choice. Exiting program.\n";
                        return 0;
                }

                do {
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
            }

            case 3:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (userType != 3);

    return 0;
}
