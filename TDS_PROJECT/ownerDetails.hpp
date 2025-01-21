#ifndef ownerDetails_h
#define ownerDetails_h

#include <iostream>
#include <iomanip>
#include "Property.hpp"

using namespace std;

class Property;

class List{
private:
    struct PropertyDetails{
        PropertyDetails* next;
    };

    struct PropertyPtr{
        PropertyPtr* propertyHead;
        PropertyPtr() : propertyHead(nullptr) {}
        PropertyPtr(PropertyPtr* p) : propertyHead(p){}
        PropertyPtr(std::nullptr_t) : propertyHead(nullptr) {} // Constructor for nullptr

        bool operator!=(std::nullptr_t) const
        {
            return propertyHead != nullptr;
        }
    };

    struct Owner{
        int OwnerID;
        char* OwnerName;
        char* OwnerContact;
        char* OwnerEmail;
        Owner* next;
        PropertyDetails* propertyHead;

        Owner() : OwnerID(0), OwnerName(nullptr), OwnerContact(nullptr), OwnerEmail(nullptr), propertyHead(nullptr), next(nullptr) {}
    };

    typedef struct Owner* OwnerPtr;
    typedef struct PropertyDetails* PropertyPtr;
    OwnerPtr head;
    OwnerPtr curr;
    OwnerPtr temp;
    int prevID;

    void formattedID(int id) const{
        cout << setw(5) << setfill('0') << id;
    }

    int getNextID() {
        int nextID = prevID + 1;

        if (nextID > 99999) {
            nextID = 1;  // Reset to 1
        }

        curr = head;
        while (curr != NULL) {
            if (curr->OwnerID == nextID) {
                nextID++;
                if (nextID > 99999) nextID = 1;
                curr = head;
                continue;
            }
            curr = curr->next;
        }
        prevID = nextID;
        return nextID;
    }

public: // functions
    List();
    ~List();

    typedef Owner* ownerPtr;

    void AddOwner(const char* OwnerName, const char* OwnerContact, const char* OwnerEmail);
    void UpdateOwner(int OwnerID, const char* OwnerName, const char* OwnerContact, const char* OwnerEmail);
    void GetOwnerDetails();
    void GetOwnerByID(int OwnerID);
    void RemoveOwner(int OwnerID);
    bool IsOwnerExist(int OwnerID);
    void UpdatePropertyCount(int OwnerID, int countChange);
    OwnerPtr FindOwnerByID(int OwnerID);
};

#endif // header_h
