#include <iostream>
#include "tenantDetails.hpp"

using namespace std;
using namespace tenantDetails;

void menu() {
    system("cls");
    cout << "\tWELCOME TO THE HOUSE OF DELTA NU!" << endl;
    cout << "\n ========= " << endl;
    cout << " Main Menu " << endl;
    cout << " =========" << endl;
    cout << "\n No. Option" << endl;
    cout << " 1.  Owner " << endl;
    cout << " 2.  Tenant " << endl;
    cout << " 3.  Exit " << endl;
}

void owner(TenantManager& manager) {
    int ownerChoice;
    char Continue;
    do {
        system("cls");
        cout << "=====" << endl;
        cout << "OWNER" << endl;
        cout << "=====" << endl;
        cout << "\n-----------------------------------------" << endl;
        cout << "No.  Option" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "1    Owner Details" << endl;
        cout << "2    Tenant Details" << endl;
        cout << "3    Payment History and Overdue" << endl;
        cout << "4    House Availability" << endl;
        cout << "5    Deposit" << endl;
        cout << "" << endl;
        cout << "0    Go back to Main Menu" << endl;
        cout << "Enter your choice (0-5): ";
        cin >> ownerChoice;

        if (ownerChoice == 0)
            return;

        if (ownerChoice < 0 || ownerChoice > 5) {
            cout << "Invalid choice. Please enter a number between 0-5." << endl;
            continue;
        }

        switch (ownerChoice) {
        case 1:
            cout << "Under maintenance landlord details function" << endl;
            break;
        case 2: {
            do {
                system("cls");
                cout << "\n------------" << endl;
                cout << "Tenant Details" << endl;
                cout << "--------------" << endl;
                cout << "1    Add Tenant" << endl;
                cout << "2    Update Tenant Information" << endl;
                cout << "3    Display Tenant Information" << endl;
                cout << "4    Remove Tenant" << endl;
                cout << "0    Back to Menu" << endl;
                cout << "\nEnter your choice (0-4): ";
                cin >> ownerChoice;

                if (ownerChoice < 0 || ownerChoice > 4) {
                    cout << "Invalid choice. Please enter a number between 0-4." << endl;
                    continue;
                }

                switch (ownerChoice) {
                //add tenant
                case 1: {
                    int TenantID;
                    string TenantIC, TenantName, TenantContact, TenantEmail, AccountNumber, BankName;

                    cout << "Enter Tenant ID: ";
                    cin >> TenantID;
                    cin.ignore();
                    cout << "Enter Tenant Name: ";
                    getline(cin, TenantName);
                    cout << "Enter Tenant IC: ";
                    getline(cin, TenantIC);
                    cout << "Enter Tenant Contact: ";
                    getline(cin, TenantContact);
                    cout << "Enter Tenant Email: ";
                    getline(cin, TenantEmail);
                    cout << "Enter Account Number: ";
                    getline(cin, AccountNumber);
                    cout << "Enter Bank Name: ";
                    getline(cin, BankName);

                    manager.AddTenant(TenantID, TenantName, TenantIC, TenantContact, TenantEmail, AccountNumber, BankName);
                }
                break;
                //update tenant
                case 2: {
                    int TenantID;
                    cout << "Enter Tenant ID: ";
                    cin >> TenantID;

                    if (!manager.DoesTenantExist(TenantID)) {
                        cout << "Tenant ID not found!" << endl;
                        break;
                    }

                     int updateChoice;
            do {
                system("cls");
                cout << "Update Tenant Information\n";
                cout << "-------------------------\n";
                cout << "1. Name\n";
                cout << "2. IC\n";
                cout << "3. Contact\n";
                cout << "4. Email\n";
                cout << "5. Account Number\n";
                cout << "6. Bank Name\n";
                cout << "0. Back\n";
                cout << "Choose the field to update (0-6): ";
                cin >> updateChoice;

                if (updateChoice == 0)
                    break;

                string newUpdate;
                cin.ignore(); // Clear newline
                cout << "Enter new value: ";
                getline(cin, newUpdate);

                switch (updateChoice) {
                case 1:
                    manager.UpdateTenant(TenantID, "Name", newUpdate);
                    break;
                case 2:
                    manager.UpdateTenant(TenantID, "IC", newUpdate);
                    break;
                case 3:
                    manager.UpdateTenant(TenantID, "Contact", newUpdate);
                    break;
                case 4:
                    manager.UpdateTenant(TenantID, "Email", newUpdate);
                    break;
                case 5:
                    manager.UpdateTenant(TenantID, "AccountNumber", newUpdate);
                    break;
                case 6:
                    manager.UpdateTenant(TenantID, "BankName", newUpdate);
                    break;
                default:
                    cout << "Invalid choice! Please select a valid option from 1-6." << endl;
                    }
                    } while (updateChoice != 0);
                }
                break;
                // get tenant details
                case 3: {
                    int tenantID;  // Declare tenantID here
                    cout << "Enter Tenant ID: ";
                    cin >> tenantID;

                    // Clear the screen *after* displaying tenant details
                    system("cls");
                    cout << "Displaying Tenant Details:\n";
                    manager.GetTenantDetails(tenantID);

                    // Pause to let the user view the output
                    cout << "\nPress Enter to return to the menu.";
                    cin.ignore(); // Clear the newline character
                    cin.get();      // Wait for user input
                }
                break;
                //remove tenant
                case 4: {
                    int tenantID;
                    cout << "Enter Tenant ID: ";
                    cin >> tenantID;
                    manager.RemoveTenant(tenantID);
                }
                break;
                case 0:
                    break;
                }
            } while (ownerChoice != 0);
        }
        break;
        case 3:
            cout << "Under maintenance payment history function" << endl;
            break;
        case 4:
            cout << "Under maintenance house availability function" << endl;
            break;
        case 5:
            cout << "Under maintenance deposit function" << endl;
            break;
        default:
            cout << "Invalid option. Please enter a number between 1-5." << endl;
            continue;
        }

        cout << "Do you want to continue? (Y/N): ";
        cin >> Continue;
        cin.ignore(); // Clear newline to prevent repetition issues

    } while (Continue == 'Y' || Continue == 'y');
}

void tenant(TenantManager& manager) {
    int tenantChoice, tenantID;
    char Continue;

    do {
        system("cls");
        cout << "======" << endl;
        cout << "TENANT" << endl;
        cout << "======" << endl;
        cout << "\n-----------------------------------------" << endl;
        cout << "1    Update Tenant Information" << endl;
        cout << "2    Display Tenant Information" << endl;
        cout << "0    Back to Main Menu" << endl;
        cout << "Enter your choice (0-2): ";
        cin >> tenantChoice;

        if (tenantChoice == 0)
            return;

        if (tenantChoice < 0 || tenantChoice > 2) {
            cout << "Invalid choice. Please enter a number between 0-2." << endl;
            continue;
        }

        switch (tenantChoice) {
        case 1: {
            int TenantID;
            cout << "Enter Tenant ID: ";
            cin >> TenantID;

            if (!manager.DoesTenantExist(TenantID)) {
                cout << "Tenant ID not found!" << endl;
                break;
            }

            int updateChoice;
            do {
                system("cls");
                cout << "Update Tenant Information\n";
                cout << "-------------------------\n";
                cout << "1. Name\n";
                cout << "2. IC\n";
                cout << "3. Contact\n";
                cout << "4. Email\n";
                cout << "5. Account Number\n";
                cout << "6. Bank Name\n";
                cout << "0. Back\n";
                cout << "Choose the field to update (0-6): ";
                cin >> updateChoice;

                if (updateChoice == 0)
                    break;

                string newUpdate;
                cin.ignore(); // Clear newline
                cout << "Enter new value: ";
                getline(cin, newUpdate);

                switch (updateChoice) {
                case 1:
                    manager.UpdateTenant(TenantID, "Name", newUpdate);
                    break;
                case 2:
                    manager.UpdateTenant(TenantID, "IC", newUpdate);
                    break;
                case 3:
                    manager.UpdateTenant(TenantID, "Contact", newUpdate);
                    break;
                case 4:
                    manager.UpdateTenant(TenantID, "Email", newUpdate);
                    break;
                case 5:
                    manager.UpdateTenant(TenantID, "AccountNumber", newUpdate);
                    break;
                case 6:
                    manager.UpdateTenant(TenantID, "BankName", newUpdate);
                    break;
                default:
                    cout << "Invalid choice! Please select a valid option from 1-6." << endl;
                }
            } while (updateChoice != 0);
        }
        break;

        case 2: {
            cout << "Enter Tenant ID: ";
            cin >> tenantID;

            // Clear the screen *after* displaying tenant details
            system("cls");
            cout << "Displaying Tenant Details:\n";
            manager.GetTenantDetails(tenantID);

            // Pause to let the user view the output
            cout << "\nPress Enter to return to the menu.";
            cin.ignore(); // Clear the newline character
            cin.get();    // Wait for user input
        }
        break;
        }

        cout << "Do you want to continue? (Y/N): ";
        cin >> Continue;
        cin.ignore(); // Clear newline to avoid repetition issues

    } while (Continue == 'Y' || Continue == 'y');
}

int main() {
    system("cls");
    cout << "\tWELCOME TO THE HOUSE OF DELTA NU!" << endl;

    TenantManager manager;
    int choice;

    do {
        menu();
        cout << "\nChoose from 1-3: ";
        cin >> choice;
        cout << "_______________________________________________________" << endl;

        switch (choice) {
        case 1:
            owner(manager);
            break;
        case 2:
            tenant(manager);
            break;
        case 3:
            cout << "See you again!!" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }

        if (choice != 3) {
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 3);

    return 0;
}
