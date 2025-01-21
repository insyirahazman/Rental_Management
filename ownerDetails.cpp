#include <cstring>
#include <iostream>
#include "ownerDetails.hpp"
using namespace std;

List::List(){
    prevID = 0;
    head = NULL;
    curr = NULL;
    temp = NULL;
}

List::~List(){
    curr = head;
    while (curr != NULL){
        temp = curr;
        curr = curr->next;

        PropertyPtr prop = temp->propertyHead;
        while (prop != NULL) {
            PropertyPtr tempProp = prop;
            prop = prop->next;
            delete tempProp;
        }

        delete[] temp->OwnerName;
        delete[] temp->OwnerContact;
        delete[] temp->OwnerEmail;
        delete temp;
    }
}

void List::AddOwner(const char* OwnerName, const char* OwnerContact, const char* OwnerEmail){

    OwnerPtr newOwner = new Owner;
    newOwner->OwnerID = getNextID();

    newOwner->OwnerName = new char[strlen(OwnerName)+1];
    strcpy(newOwner->OwnerName, OwnerName);

    newOwner->OwnerContact = new char[strlen(OwnerContact)+1];
    strcpy(newOwner->OwnerContact, OwnerContact);

    newOwner->OwnerEmail = new char[strlen(OwnerEmail)+1];
    strcpy(newOwner->OwnerEmail, OwnerEmail);

    newOwner->propertyHead = NULL;
    newOwner->next = NULL;

    if(head == NULL){
        head = newOwner;
    } else{
        curr = head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = newOwner;
    }
    cout << "\nOwner added successfully! " << endl;
    cout << "Name: " << OwnerName << endl;
    cout << "ID  : ";
    formattedID(newOwner->OwnerID);
    cout << endl;
}

void List::AddPropertyToOwner(int OwnerID, int PropertyID){
    curr = head;
    while (curr != NULL) {
        if (curr->OwnerID == OwnerID) {
            PropertyPtr newProperty = new Property;
            newProperty->PropertyID = PropertyID;
            newProperty->next = NULL;

            if (curr->propertyHead == NULL) {
                curr->propertyHead = newProperty;
            } else {
                PropertyPtr prop = curr->propertyHead;
                while (prop->next != NULL) {
                    prop = prop->next;
                }
                prop->next = newProperty;
            }
            cout << "Property added to Owner ID: ";
            formattedID(OwnerID);
            cout << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Owner ID: " << OwnerID << " not found." << endl;
}


void List::UpdateOwner(int OwnerID, const char* OwnerName, const char* OwnerContact, const char* OwnerEmail){
    curr = head;
    while (curr != NULL){
        if (curr->OwnerID == OwnerID){
            delete[] curr->OwnerName;
            delete[] curr->OwnerContact;
            delete[] curr->OwnerEmail;

            curr->OwnerName = new char[strlen(OwnerName)+1];
            strcpy(curr->OwnerName, OwnerName);

            curr->OwnerContact = new char[strlen(OwnerContact)+1];
            strcpy(curr->OwnerContact, OwnerContact);

            curr->OwnerEmail = new char[strlen(OwnerEmail)+1];
            strcpy(curr->OwnerEmail, OwnerEmail);

            cout << "Owner details updated successfully." << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Owner ID: " << OwnerID << " not found." << endl;
}

void List::GetOwnerDetails(){
    if(head == NULL){
        cout << "No owners found in the system. " << endl;
        return;
    }
    curr = head;
    while (curr != NULL){
        cout << "Owner ID: ";
        formattedID(curr->OwnerID);
        cout << endl;
        cout << "Name       : " << curr->OwnerName << endl;
        cout << "Contact    : " << curr->OwnerContact << endl;
        cout << "Email      : " << curr->OwnerEmail << endl;

       PropertyPtr prop = curr->propertyHead;
        if (prop == NULL) {
            cout << "Properties : None" << endl;
        } else {
            cout << "Properties :" << endl;
            while (prop != NULL) {
                cout << "   - Property ID: " << prop->PropertyID << endl;
                prop = prop->next;
            }
        }
        cout << "\n----------------------------------------" << endl;
        curr = curr->next;
    }
}

void List::GetOwnerByID(int OwnerID){
    curr = head;
    while(curr != NULL){
        if(curr->OwnerID == OwnerID){
            cout << "Owner ID: " << curr->OwnerID << endl;
            cout << "Name    : " << curr->OwnerName << endl;
            cout << "Contact : " << curr->OwnerContact << endl;
            cout << "Email   : " << curr->OwnerEmail << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Owner ID: " << OwnerID << " not found." << endl;
}

void List::RemoveOwner(int OwnerID){
    if(head == NULL){
        cout << "There are no owners in the system." << endl;
        return;
    }

    temp = head;
    curr = head;

    while(curr != NULL && curr->OwnerID != OwnerID){
        temp = curr;
        curr = curr->next;
    }

    if(curr == NULL){
        cout << "Owner ID: " << OwnerID << " not found." << endl;
        return;
    }

    if(curr == head){
        head = head->next;
    } else{
        temp->next = curr->next;
    }

    cout << "\nRemoving owner:" << endl;
    cout << "Name: " << curr->OwnerName << endl;
    cout << "ID  : " << curr->OwnerID << endl;

    delete[] curr->OwnerName;
    delete[] curr->OwnerContact;
    delete[] curr->OwnerEmail;
    delete curr;

    cout << "Owner removed successfully." << endl;
}

bool List::IsOwnerExist(int OwnerID){
    curr = head;
    while (curr != NULL){
        if (curr->OwnerID == OwnerID){
            return true;
        }
        curr = curr->next;
    }
    return false;
}
