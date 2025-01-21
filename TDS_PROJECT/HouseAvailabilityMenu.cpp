#include "HouseAvailabilityMenu.hpp"
#include <iostream>

using namespace std;

HouseAvailabilityMenu::HouseAvailabilityMenu() {}

void HouseAvailabilityMenu::addNewProperty() {
    string address, details, status;
    float deposit, rent;

    cout << "Enter property address: ";
    cin >> address;

    cout << "Enter unit details (e.g., 2bed 2bath): ";
    cin >> details;

    cout << "Enter rent deposit amount: ";
    cin >> deposit;

    cout << "Enter monthly rent amount: ";
    cin >> rent;

    cout << "Enter occupancy status (empty/occupied): ";
    cin >> status;

    int id = propertyManager.AddProperty(ownerList, -1, -1, address, details, deposit, rent, status);
    if (id != -1) {
        cout << "Property added successfully! Property ID: " << id << endl;
    } else {
        cout << "Failed to add property. Storage might be full." << endl;
    }
}

void HouseAvailabilityMenu::updateProperty() {
    int id;
    string address, details, status;
    float deposit, rent;

    cout << "Enter property ID to update: ";
    cin >> id;

    cout << "Enter new property address: ";
    cin >> address;

    cout << "Enter new unit details: ";
    cin >> details;

    cout << "Enter new rent deposit amount: ";
    cin >> deposit;

    cout << "Enter new monthly rent amount: ";
    cin >> rent;

    cout << "Enter new occupancy status (empty/occupied): ";
    cin >> status;

    if (propertyManager.UpdateProperty(id, address, details, deposit, rent, status)) {
        cout << "Property updated successfully!" << endl;
    } else {
        cout << "Property not found!" << endl;
    }
}

void HouseAvailabilityMenu::updateStatus() {
    int id;
    string status;

    cout << "Enter property ID: ";
    cin >> id;

    cout << "Enter new status (empty/occupied): ";
    cin >> status;

    if (propertyManager.UnitStatus(id, status)) {
        cout << "Status updated successfully!" << endl;
    } else {
        cout << "Property not found!" << endl;
    }
}

void HouseAvailabilityMenu::checkStatus() {
    int id;
    cout << "Enter property ID: ";
    cin >> id;

    const string& status = propertyManager.CheckVacancy(id);
    cout << "Property status: " << status << endl;
}

void HouseAvailabilityMenu::viewVacantProperties() {
    int vacantUnits[HASH_SIZE];
    int count;
    propertyManager.VacantUnits(vacantUnits, count);

    cout << "Vacant Properties:" << endl;
    cout << "----------------" << endl;
    if (count == 0) {
        cout << "No vacant properties found." << endl;
    } else {
        for (int i = 0; i < count; i++) {
            cout << "Property ID: " << vacantUnits[i] << endl;
        }
    }
}

void HouseAvailabilityMenu::removeProperty() {
    int id;
    cout << "Enter property ID to remove: ";
    cin >> id;

    if (propertyManager.RemoveProperty(id)) {
        cout << "Property removed successfully!" << endl;
    } else {
        cout << "Property not found!" << endl;
    }
}

void HouseAvailabilityMenu::displayMenu() {
    int choice;
    char Continue;

    do {
        system("cls");
        cout << "=================" << endl;
        cout << "House Availability" << endl;
        cout << "=================" << endl;
        cout << "\n-----------------------------------------" << endl;
        cout << "No.  Option" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "1    Add New Property" << endl;
        cout << "2    Update Property Details" << endl;
        cout << "3    Update Property Status" << endl;
        cout << "4    Check Property Status" << endl;
        cout << "5    View All Vacant Properties" << endl;
        cout << "6    Remove Property" << endl;
        cout << "" << endl;
        cout << "0    Go back to Landlord Menu" << endl;

        cout << "Enter your choice (0-6): ";
        cin >> choice;

        if (choice == 0) return;

        switch (choice) {
            case 1:
                addNewProperty();
                break;
            case 2:
                updateProperty();
                break;
            case 3:
                updateStatus();
                break;
            case 4:
                checkStatus();
                break;
            case 5:
                viewVacantProperties();
                break;
            case 6:
                removeProperty();
                break;
            default:
                cout << "Invalid option. Please enter a number between 0-6." << endl;
                continue;
        }

        cout << "Do you want to continue? (Y/N): ";
        cin >> Continue;

    } while (Continue == 'Y' || Continue == 'y');
}
