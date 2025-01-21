#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

#include "Property.hpp"
#include "tenantDetails.hpp"
#include "ownerDetails.hpp"
#include "deposit.hpp"
#include "QueueOverdue.hpp"

using namespace std;
using namespace tenantDetails;
using namespace Overdue1;

void menu();
void landlord(TenantManager& manager, List& OwnerList, DepositManager& depositManager, Property& propertyManager);
void tenant(TenantManager& manager, DepositManager& depositManager, Property& propertyManager);
void manageOwnerDetails(List& OwnerList, Property& propertyManager);
void manageTenantDetails(TenantManager& manager);
void promptContinue();

// Struct to store payment information
struct Payment {
    string UserID;
    string PaymentDate;
    string remarks;
    string paymentYear;
    string paymentMonth;
    double PaymentAmount;
};

Payment paymentRecords[100];
//Overdue overdueRecords[MAX_SIZE];
int paymentSize = 0;
string UserID;
Queue overdueQueue;

void AddPayment(Payment payments[], int& size, int maxSize)
{
    system("cls");
    cout << "\n============== Add Payment ==============" << endl;
    if (size >= maxSize)
    {
        cout << "Storage is full. System is unable to store payment records." << endl;
        promptContinue();
        return;
    }
    Payment newPayment;
    cout << "Enter the Tenant ID: ";
    cin >> newPayment.UserID;
    cout << "Enter payment date (YYYY-MM-DD): ";
    cin >> newPayment.PaymentDate;
    cout << "Enter total amount paid RM: ";
    while (!(cin >> newPayment.PaymentAmount))
    {
        cin.clear(); // Clear the error flag
        cin.ignore(1000, '\n'); // Discard invalid input
        cout << "Invalid input. Enter a numeric value for the amount: ";
    }

    cin.ignore(); // Clear the newline character left in the buffer
    cout << "Enter remarks: ";
    getline(cin, newPayment.remarks); // Use getline to handle spaces
    newPayment.paymentYear = newPayment.PaymentDate.substr(0, 4);
    newPayment.paymentMonth = newPayment.PaymentDate.substr(5, 2);

    payments[size++] = newPayment;
    cout << "Payment record added successfully." << endl;
    promptContinue();
}

void DeletePayment(Payment payments[], int& size, const string& UserID)
{
    system("cls");
    cout << "\n============== Delete Payment ==============" << endl;
    cout << "Enter Tenant ID to delete records: ";
    int index = -1;
    //to find a record by using paymentID
    for (int i = 0; i < size; i++)
    {
        if (payments[i].UserID == UserID)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        cout << "Payment record with Tenant ID " << UserID << " not found." << endl;
        promptContinue();
        return;
    }    // Shift elements to fill the gap

    for (int i = index; i < size - 1; i++)
    {
        payments[i] = payments[i + 1];
    }

    size--;
    cout << "Payment record with Tenant ID " << UserID << " has been deleted." << endl;
    promptContinue();
}

void ViewAllPayment(Payment payments[], int size)
{
    system("cls");
    cout << "\n============== View All Payment ==============" << endl;
    cout << "All payments records: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "Payment ID: " << payments[i].UserID << endl;
        cout << "Payment date: " << payments[i].PaymentDate << endl;
        cout << "Total amount: " << payments[i].PaymentAmount << endl;
        cout << "Remarks: " << payments[i].remarks << endl;
    }
    promptContinue();
}

void SortPaymentsByID(Payment payments[], int size)
{
    system("cls");
    cout << "\n============== Sort Payments By ID ==============" << endl;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (payments[j].UserID > payments[j + 1].UserID)
            {
                Payment temp = payments[j];
                payments[j] = payments[j + 1];
                payments[j + 1] = temp;
            }
        }
    }
    cout << "Payments sorted by Tenant ID." << endl;
    promptContinue();
}

void AddOverdue(Queue& overdueQueue)
{
    system("cls");
    Overdue newOverdue;
    cout << "\n============== Add Overdue ==============" << endl;
    cout << "Enter Tenant ID to add overdue details: ";
    cin >> newOverdue.UserID;

    cout << "Enter the total overdue (RM): ";
    while (!(cin >> newOverdue.TotalOverdue))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a numeric value: ";
    }
    cin.ignore();
    cout << "Enter due date of overdue payment (YYYY-MM-DD): ";
    getline(cin, newOverdue.PayBeforeDate);

    overdueQueue.enqueue(newOverdue);
    cout << "Overdue data added successfully." << endl;
    promptContinue();
}

Queue::Queue() : front(0), back(0), count(0) {}

Queue::~Queue() {}

bool Queue::isEmpty()
{
    return count == 0;
}

void Queue::enqueue(QueueItemType newItem)
{
    if (count < MAX_QUEUE)
    {
        items[back] = newItem;
        back = (back + 1) % MAX_QUEUE;
        count++;
    }
}

void ViewPayment(Payment payments[], int size)
{
    system("cls");
    cout << "\n============== View Payment ==============" << endl;
    string SearchID;
    cout << "Enter Tenant ID to view payment records: ";
    cin >> SearchID;

    bool found = false; //flag to check whether records are found

    for (int i = 0; i < size; i++)
    {
        if (payments[i].UserID == SearchID)
        {
            cout << "\nPayment Records Found:" << endl;
            cout << "----------------------\n";
            cout << "Tenant ID: " << payments[i].UserID << endl;
            cout << "Payment Date: " << payments[i].PaymentDate << endl;
            cout << "Payment Amount (RM): " << payments[i].PaymentAmount << endl;
            cout << "Remarks: " << payments[i].remarks << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "Payment record with Tenant ID " << SearchID << " not found." << endl;
        return;
    }
    promptContinue();
}

void ViewOverdue(Queue& overdueQueue)
{
    system("cls");
    cout << "\n============== View Overdue ==============" << endl;
    if (overdueQueue.isEmpty())
    {
        cout << "No overdue records to display." << endl;
        promptContinue();
        return;
    }

    cout << "Processing overdue records: " << endl;
    while (!overdueQueue.isEmpty())
    {
        Overdue currentOverdue = overdueQueue.getFront();
        overdueQueue.dequeue();

        cout << "-------------------------\n";
        cout << "Tenant ID: " << currentOverdue.UserID << endl;
        cout << "Total Overdue (RM): " << currentOverdue.TotalOverdue << endl;
        cout << "Please pay before: " << currentOverdue.PayBeforeDate << endl;
    }
    promptContinue();
}

void Queue::dequeue()
{
    if (!isEmpty())
    {
        front = (front + 1) % MAX_QUEUE;
        count--;
    }
    else
    {
        cout << "Queue is empty. Cannot dequeue." << endl;
    }
}

QueueItemType Queue::getFront()
{
    if (!isEmpty())
    {
        return items[front];
    }
    cout << "Queue is empty. No front item available." << endl;
    return QueueItemType();
}

void PaymentMenu(TenantManager& manager)
{
    system("cls");
    int option;
    do{
        cout << "===========================\n";
        cout << "Payment History and overdue\n";
        cout << "===========================\n";

        cout << "1. Add Payment Records\n";
        cout << "2. Delete Payment Records\n";
        cout << "3. View All Payment Records\n";
        cout << "4. Add Overdue Records\n";
        cout << "0. Back to main menu\n";

        cout << "Please enter your choice: ";
        cin >> option;

        switch (option)
        {
            case 0:
                return;

            case 1:
                AddPayment(paymentRecords, paymentSize, 100);
                SortPaymentsByID(paymentRecords, paymentSize);
                break;

            case 2:
                DeletePayment(paymentRecords, paymentSize, UserID);
                break;

            case 3:
                ViewAllPayment(paymentRecords, paymentSize);
                break;

            case 4:
                AddOverdue(overdueQueue);
                break;

            default:
                cout << "Invalid option. Please enter a number between 0-4." << endl;
                promptContinue();
        }
    } while(true);
}

void TenantPaymentMenu()
{
    system("cls");
    int paymentoption;

    do{
        cout << "============================\n";
        cout << "Payment History and Overdue\n";
        cout << "============================\n";
        cout << "1. View Payments History\n";
        cout << "2. View Payments Overdue\n";
        cout << "0. Back to main menu\n";

        cout << "Enter an option (0-2): ";
        cin >> paymentoption;
        cin.ignore();
        switch (paymentoption)
        {
            case 0:
                return;

            case 1:
                ViewPayment(paymentRecords, paymentSize);
                break;

            case 2:
                ViewOverdue(overdueQueue);
                break;

            default:
                cout << "Invalid option. Please enter a number between 0-2." << endl;
                promptContinue();
        }
    } while (paymentoption != 0);
}

void houseAvailabilityLandlord(Property& propertyManager)
{
    system("cls");
    int houseOwnerchoice;
    char Continue;

    do{
        cout << "==================" << endl;
        cout << "House Availability" << endl;
        cout << "==================" << endl;
        cout << "\n----------------------------------------- " << endl;
        cout << " No.  Option" << endl;
        cout << "----------------------------------------- " << endl;
        cout << "1    Add New Property" << endl;
        cout << "2    Update Property Details" << endl;
        cout << "3    Update Property Status" << endl;
        cout << "4    Check Property Status" << endl;
        cout << "5    View All Vacant Properties" << endl;
        cout << "6    Remove Property" << endl;
        cout << "" << endl;
        cout << "0    Go back to Owner Menu" << endl;
        cout << "Enter an option (0-6): ";
        cin >> houseOwnerchoice;
        cin.ignore();

        if (houseOwnerchoice == 0)
            return;

        if (houseOwnerchoice < 0 || houseOwnerchoice > 6)
        {
            cout << "Invalid choice. Please enter a number between 0-6." << endl;
            promptContinue();
            continue;
        }

        switch (houseOwnerchoice)
        {
        case 1:
            {
                string address, details, status;
                float deposit, rent;
                static int nextId = 001;
                cout << "\n============== Add Property ==============" << endl;
                cout << "Enter property address: ";
                cin.ignore();
                getline(cin, address);
                cout << "Enter unit details (e.g., 2bed 2bath): ";
                getline(cin, details);
                cout << "Enter rent deposit amount: ";
                cin >> deposit;
                cout << "Enter monthly rent amount: ";
                cin >> rent;
                cout << "Enter occupancy status (empty/occupied): ";
                cin >> status;

                int id = propertyManager.AddProperty(nextId++, address, details, deposit, rent, status);
                if (id != -1)
                {
                    cout << "Property added successfully! Property ID: " << id << endl;
                }
                else
                {
                    cout << "Failed to add property. Storage might be full." << endl;
                }
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            }

            case 2:
                {
                    int id;
                    string address, details, status;
                    float deposit, rent;
                    cout << "\n============== Update Property ==============" << endl;
                    cout << "Enter property ID to update: ";
                    cin >> id;

                    cout << "Enter new property address: ";
                    cin.ignore();
                    getline(cin, address);

                    cout << "Enter new unit details: ";
                    getline(cin, details);

                    cout << "Enter new rent deposit amount: ";
                    cin >> deposit;

                    cout << "Enter new monthly rent amount: ";
                    cin >> rent;

                    cout << "Enter new occupancy status (empty/occupied): ";
                    cin >> status;

                    if (propertyManager.UpdateProperty(id, address, details, deposit, rent, status))
                    {
                        cout << "Property updated successfully!" << endl;
                    }
                    else
                    {
                        cout << "Property not found!" << endl;
                    }
                    cout << "Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                    break;
                }

            case 3:
                {
                    int id;
                    string status;
                    cout << "\n============== Update Property Status ==============" << endl;
                    cout << "Enter property ID: ";
                    cin >> id;

                    cout << "Enter new status (empty/occupied): ";
                    cin >> status;

                    if (propertyManager.UnitStatus(id, status))
                    {
                        cout << "Status updated successfully!" << endl;
                    }
                    else
                    {
                        cout << "Property not found!" << endl;
                    }
                    cout << "Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                    break;
                }

            case 4:
                {
                    int id;
                    cout << "\n============== Property Status ==============" << endl;
                    cout << "Enter property ID: ";
                    cin >> id;

                    const string& status = propertyManager.CheckVacancy(id);
                    cout << "Property status: " << status << endl;
                    cout << "Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                    break;
                }

            case 5:
                {
                    int vacantUnits[HASH_SIZE];
                    int count;
                    propertyManager.VacantUnits(vacantUnits, count);
                    cout << "\n============== Vacant Properties ==============" << endl;

                    if (count == 0)
                    {
                        cout << "No vacant properties found." << endl;
                    }
                    else
                    {
                        for (int i = 0; i < count; i++)
                        {
                            cout << "Property ID: " << vacantUnits[i] << endl;
                        }
                    }
                    cout << "Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                    break;
                }

            case 6:
                {
                    int id;
                    cout << "\n============== Remove Properties ==============" << endl;
                    cout << "Enter property ID to remove: ";
                    cin >> id;

                    if (propertyManager.RemoveProperty(id))
                    {
                        cout << "Property removed successfully!" << endl;
                    }
                    else
                    {
                        cout << "Property not found!" << endl;
                    }
                    cout << "Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                    break;
                }

            default:
                cout << "Invalid option. Please enter a number between 0-6." << endl;

            } promptContinue();

    } while(true);
}

// Update tenant menu
void updateTenantMenu(TenantManager& manager, int TenantID)
{
    system("cls");
    // Display current tenant details before updating
    cout << manager.GetTenantDetails(TenantID) << endl;

    int updateChoice;
    char Continue;
    string newValue;

    // Choose what to update
    do
    {
        cout << "---------------------\n";
        cout << "Update Tenant Details\n";
        cout << "---------------------\n";
        cout << "1. Name\n";
        cout << "2. IC\n";
        cout << "3. Contact\n";
        cout << "4. Email\n";
        cout << "5. Account Number\n";
        cout << "6. Bank Name\n";
        cout << "0. Back\n";
        cout << "Choose which to update (0-6): ";
        cin >> updateChoice;
        cout << "\n---------------------\n";
        cin.ignore();

        if (updateChoice == 0)
            break;

        cout << "Enter new value: ";
        getline(cin, newValue);

        // Switch based on what to update
        switch (updateChoice) {
            case 1:
                manager.UpdateTenant(TenantID, "Name", newValue);
                break;
            case 2:
                manager.UpdateTenant(TenantID, "IC", newValue);
                break;
            case 3:
                manager.UpdateTenant(TenantID, "Contact", newValue);
                break;
            case 4:
                manager.UpdateTenant(TenantID, "Email", newValue);
                break;
            case 5:
                manager.UpdateTenant(TenantID, "AccountNumber", newValue);
                break;
            case 6:
                manager.UpdateTenant(TenantID, "BankName", newValue);
                break;
            default:
                cout << "Invalid choice! Please select a valid option." << endl;
                promptContinue();
        }
        cout << "Field updated successfully.\n";
        promptContinue();
    } while (true);
}

// Function to prompt the user to press Enter to continue
void promptContinue() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void menu()
{
    system("cls");
    cout << "\tWELCOME TO THE HOUSE OF DELTA NU!" << endl;
    cout << "" << endl;
    cout << "=========" << endl;
    cout << "Main Menu" << endl;
    cout << "=========" << endl;
    cout << "" << endl;
    cout << " No. Option" << endl;
    cout << " 1.  Owner " << endl;
    cout << " 2.  Tenant " << endl;
    cout << " 3.  Exit " << endl;
    cout<<""<<endl;
    cout<<"Enter an option (1-3): ";
}

void landlord(TenantManager& manager, List& OwnerList, DepositManager& depositManager, Property& propertyManager)
{
    system("cls");
    int landlordChoice;

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
        cin >> landlordChoice;

        switch (landlordChoice) {
        case 0:
            return; // Exit to main menu
        case 1:
            manageOwnerDetails(OwnerList, propertyManager);
            break;
        case 2:
            manageTenantDetails(manager);
            break;
        case 3:
            PaymentMenu(manager);
            break;
        case 4:
            houseAvailabilityLandlord(propertyManager);
            break;
        case 5:
            DepositManager(depositManager);
            break;
        default:
            cout << "Invalid choice. Please enter a number between 0-5." << endl;
            promptContinue();
        }
    } while (landlordChoice != 0);
}

void manageOwnerDetails(List& OwnerList, Property& propertyManager)
{
    int ownerChoice;

    do {
        system("cls");
        cout << "=========================================" << endl;
        cout << "               OWNER DETAILS             " << endl;
        cout << "=========================================" << endl;
        cout << "1    Add Owner" << endl;
        cout << "2    Update Owner" << endl;
        cout << "3    Remove Owner" << endl;
        cout << "4    Display All Owners" << endl;
        cout << "5    Add Property To Owner" << endl;
        cout << "0    Back to Owner Menu" << endl;
        cout << "Enter your choice (0-5): ";
        cin >> ownerChoice;

        switch (ownerChoice) {
        case 0:
            return; // Return to landlord menu
        case 1:
            addOwner(OwnerList);
            break;
        case 2:
            updateOwner(OwnerList);
            break;
        case 3:
            removeOwner(OwnerList);
            break;
        case 4:
            displayOwners(OwnerList);
            break;
        case 5:
            addPropertyToOwner(OwnerList, propertyManager);
            break;
        default:
            cout << "Invalid choice. Please enter a number between 0-5." << endl;
            promptContinue();
        }
    } while (ownerChoice != 0);
}

void manageTenantDetails(TenantManager& manager)
{
    int tenantChoice;

    do {
        system("cls");
        cout << "=========================================" << endl;
        cout << "               TENANT DETAILS            " << endl;
        cout << "=========================================" << endl;
        cout << "1    Add Tenant" << endl;
        cout << "2    Update Tenant Information" << endl;
        cout << "3    Display Tenant Information" << endl;
        cout << "4    Remove Tenant" << endl;
        cout << "0    Back to Owner Menu" << endl;
        cout << "Enter your choice (0-4): ";
        cin >> tenantChoice;

        switch (tenantChoice) {
        case 0:
            return; // Return to landlord menu
        case 1:
            addTenant(manager);
            break;
        case 2:
            updateTenant(manager);
            break;
        case 3:
            displayTenant(manager);
            break;
        case 4:
            removeTenant(manager);
            break;
        default:
            cout << "Invalid choice. Please enter a number between 0-4." << endl;
            promptContinue();
        }
    } while (tenantChoice != 0);
}

void tenant(TenantManager& manager, DepositManager& depositManager, Property& propertyManager)
{
    int tenantChoice;
    int tenantID;
    char Continue;

    system("cls");
    cout << "======" << endl;
    cout << "TENANT" << endl;
    cout << "======" << endl;
    cout << "\n-----------------------------------------" << endl;
    cout << "1    Tenant Details" << endl;
    cout << "2    Payment History and Overdue" <<endl;
    cout << "3    Deposit Return" << endl;
    cout << "4    House Availability" << endl;
    cout << "" << endl;
    cout << "0    Go back to Main Menu" << endl;

    do
    {
        cout << "Enter your choice (0-4): ";
        cin >> tenantChoice;
        cin.ignore();

        if (tenantChoice == 0)
        return;

        if (tenantChoice < 0 || tenantChoice > 5)
        {
            cout << "Invalid choice. Please enter a number between 0-4." << endl;
            continue;
        }

    switch (tenantChoice)
    {
        case 1:
            int subChoice;
            do
            {
                system("cls");
                cout << "=========================================" << endl;
                cout << "               TENANT DETAILS            " << endl;
                cout << "=========================================" << endl;
                cout << "1    Update Tenant Information" << endl;
                cout << "2    Display Tenant Information" << endl;
                cout << "0    Back to Tenant Menu" << endl;
                cout << "\nEnter your choice (0-2): ";
                cin >> tenantChoice;

                // Exit tenant details menu
                if (tenantChoice == 0)
                    break;

                // Input choice less or more than 0-2
                if (tenantChoice < 0 || tenantChoice > 2)
                {
                    cout << "Invalid choice. Please enter a number between 0-2." << endl;
                    cout << "Press Enter to continue...";
                    cin.ignore();
                    cin.get();
                    continue;
                }

                // Switch based on choice
                switch (tenantChoice)
                {
                    // Update tenant details
                    case 1:
                        int TenantID;
                        cout << "Enter Tenant ID: ";
                        cin >> TenantID;

                        if (!manager.DoesTenantExist(TenantID))
                        {
                            cout << "Tenant ID not found!" << endl;
                            cout << "Press Enter to continue...";
                            cin.ignore();
                            cin.get();
                            break;
                        }

                        // Call the update tenant menu function
                        updateTenantMenu(manager, TenantID);
                        break;

                    // Display tenant details
                    case 2:
                        int tenantID;
                        cout << "Enter Tenant ID: ";
                        cin >> tenantID;
                        system("cls");
                        cout << manager.GetTenantDetails(tenantID) << endl;
                        cout << "Press Enter to continue...";
                        cin.ignore();
                        cin.get();
                        break;
                }
            } while(true);
            break;
        case 2:
             TenantPaymentMenu();
            break;
        case 3:
             depositManager.ViewTenantDeposit(tenantID);
            break;
        case 4:
             cout << "Under maintenance house availability function" << endl;
            break;
        default:
            cout << "Invalid option. Please enter a number between 0-4." << endl;

    } promptContinue();

  }while (tenantChoice != 0);

  cout<<"_______________________________________________________"<<endl;
}

int main(){
    system("cls");
    cout<<"WELCOME TO THE HOUSE OF DELTA NU!"<<endl;

    DepositManager depositManager;
    TenantManager manager;
    List OwnerList;
    Property propertyManager;
    int choice;

    do
    {
        menu();
        cin>>choice;
        cout<<"_______________________________________________________"<<endl;

        switch (choice)
        {
        case 1:
            landlord(manager, OwnerList, depositManager, propertyManager);
            break;
        case 2:
            tenant(manager, depositManager, propertyManager);
            break;
        case 3:
            cout<<"~Thank you for using our system~\n";
            cout<<"         See you again!!"<<endl;
            break;
        default:
            cout<<"Invalid choice."<<endl;
            promptContinue();
            break;
        }
        if (choice != 3)
        {
            promptContinue();
        }

    }while (choice !=3);

    return 0;
}
