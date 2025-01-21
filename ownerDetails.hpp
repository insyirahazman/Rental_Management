#ifndef ownerDetails_h
#define ownerDetails_h
#include <iomanip>
using namespace std;

class List{
private:

    typedef struct Property{
        int PropertyID;
        Property* next;
    }* PropertyPtr;

    typedef struct Owner{
        int OwnerID;
        char* OwnerName;
        char* OwnerContact;
        char* OwnerEmail;
        PropertyPtr propertyHead;
        Owner* next;
    }* OwnerPtr;

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

    void AddOwner(const char* OwnerName, const char* OwnerContact, const char* OwnerEmail);
    void AddPropertyToOwner(int OwnerID, int PropertyID);
    void UpdateOwner(int OwnerID, const char* OwnerName, const char* OwnerContact, const char* OwnerEmail);
    void GetOwnerDetails();
    void GetOwnerByID(int OwnerID);
    void RemoveOwner(int OwnerID);
    bool IsOwnerExist(int OwnerID);
};

#endif // header_h
