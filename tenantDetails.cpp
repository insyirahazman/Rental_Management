#include <iostream>
#include "tenantDetails.hpp"

using namespace std;

namespace tenantDetails {

    // Constructor for the TenantManager class
    TenantManager::TenantManager() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            tenants[i] = nullptr;
        }
    }

    // Hash function to calculate hash value
    int TenantManager::hashFunction(int TenantID) const {
        return TenantID % TABLE_SIZE;
    }

    // Add a new tenant
    void TenantManager::AddTenant(int TenantID, const string& TenantName, const string& TenantIC, const string& TenantContact,
                                  const string& TenantEmail, const string& AccountNumber, const string& BankName) {
        int index = hashFunction(TenantID);

        Tenant* newTenant = new Tenant(TenantID, TenantName, TenantIC, TenantContact, TenantEmail,
                                       AccountNumber, BankName, 0.0f, "", "", 0.0f, "Not Paid");

        if (tenants[index] == nullptr) {
            tenants[index] = newTenant;
        } else {
            Tenant* current = tenants[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newTenant;
        }

        cout << "Tenant added successfully!" << endl;
    }

    // Update a specific field of an existing tenant
    void TenantManager::UpdateTenant(int TenantID, const string& field, const string& newUpdate) {
        int index = hashFunction(TenantID);

        Tenant* current = tenants[index];
        while (current != nullptr) {
            if (current->TenantID == TenantID) {
                if (field == "Name") current->TenantName = newUpdate;
                else if (field == "Contact") current->TenantContact = newUpdate;
                else if (field == "Email") current->TenantEmail = newUpdate;
                else if (field == "AccountNumber") current->AccountNumber = newUpdate;
                else if (field == "BankName") current->BankName = newUpdate;
                else {
                    cout << "Invalid field name!" << endl;
                    return;
                }
                cout << "Tenant information updated successfully!" << endl;
                return;
            }
            current = current->next;
        }
        cout << "Error: Tenant ID not found!" << endl;
    }

    // Get details of a tenant and return it as a string
    string TenantManager::GetTenantDetails(int TenantID) {
        int index = hashFunction(TenantID);

        Tenant* current = tenants[index];
        while (current != nullptr) {
            if (current->TenantID == TenantID) {
                string tenantInfo;
                tenantInfo += "Tenant ID: " + to_string(current->TenantID) + "\n";
                tenantInfo += "Name: " + current->TenantName + "\n";
                tenantInfo += "IC: " + current->TenantIC + "\n";
                tenantInfo += "Contact: " + current->TenantContact + "\n";
                tenantInfo += "Email: " + current->TenantEmail + "\n";
                tenantInfo += "Account Number: " + current->AccountNumber + "\n";
                tenantInfo += "Bank Name: " + current->BankName + "\n";
                tenantInfo += "Rental Amount: " + to_string(current->RentalAmount) + "\n";
                tenantInfo += "Tenancy Period: " + current->TenancyPeriod + "\n";
                tenantInfo += "Tenancy End Date: " + current->TenancyEndDate + "\n";
                tenantInfo += "Deposit Status: " + current->DepositStatus + "\n";

                return tenantInfo;  // Return the formatted details string
            }
            current = current->next;
        }
        return "Error: Tenant ID not found!";  // Return an error message if the tenant ID is not found
    }

    // Remove a tenant
    void TenantManager::RemoveTenant(int TenantID) {
        int index = hashFunction(TenantID);

        Tenant* current = tenants[index];
        Tenant* prev = nullptr;
        while (current != nullptr) {
            if (current->TenantID == TenantID) {
                if (prev == nullptr) {
                    tenants[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                cout << "Tenant removed successfully!" << endl;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Error: Tenant ID not found!" << endl;
    }

    // Check if a tenant exists
    bool TenantManager::DoesTenantExist(int TenantID) const {
        int index = hashFunction(TenantID);

        Tenant* current = tenants[index];
        while (current != nullptr) {
            if (current->TenantID == TenantID) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Check if the tenant manager is empty
    bool TenantManager::isEmpty() const {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (tenants[i] != nullptr) {
                return false;
            }
        }
        return true;
    }

}
