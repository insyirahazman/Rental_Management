#include <iostream>
#include <string>
#include "Property.hpp"
using namespace std;

Property::Property():nextPropertyID(1), currentSize(0)
{
    hashTable = new PropertyDetails[HASH_SIZE];
    initializeHashTable();
}

Property::~Property()
{
    delete[] hashTable;
}

void Property::initializeHashTable()
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        hashTable[i].isOccupied = false;
        hashTable[i].PropertyID = -1;  // -1 indicates empty slot
    }
}

void Property::hash(const PropertyDetails* storageArea, int size, int PropertyID, int& storeIndex, bool& found, int probeStopValue)
{
    int counter = 1;
    found = true;
    storeIndex = PropertyID % size;

    while(storageArea[storeIndex].PropertyID != probeStopValue && storageArea[storeIndex].isOccupied)
    {
        storeIndex = (storeIndex + 1) % size;
        counter++;
        if (counter > size)
        {
            found = false;
            break;
        }
    }
}

Property::PropertyDetails Property::createPropertyDetails(int PropertyID, const string& PropertyAddress, const string& UnitDetails, float RentDeposit, float RentAmt, const string& OccupancyStatus)
{
    Property::PropertyDetails newProperty;
    newProperty.PropertyID = PropertyID;
    newProperty.PropertyAddress = PropertyAddress;
    newProperty.UnitDetails = UnitDetails;
    newProperty.RentDeposit = RentDeposit;
    newProperty.RentAmt = RentAmt;
    newProperty.OccupancyStatus = OccupancyStatus;
    newProperty.isOccupied = true;

    return newProperty;
}

int Property::AddProperty(int PropertyID, const string& PropertyAddress, const string& UnitDetails, float RentDeposit, float RentAmt, const string& OccupancyStatus)
{
    if(currentSize >= HASH_SIZE)
    {
        return -1;
    }

    PropertyID = nextPropertyID;
    int storeIndex;
    bool found;

    hash(hashTable, HASH_SIZE, PropertyID, storeIndex, found, -1);

    if(!found)
    {
        return -1;
    }

    hashTable[storeIndex] = createPropertyDetails(PropertyID, PropertyAddress, UnitDetails, RentDeposit, RentAmt, OccupancyStatus);

    currentSize++;
    nextPropertyID++;
    return PropertyID;
}

bool Property::UpdateProperty(int PropertyID, const string& PropertyAddress, const string& UnitDetails, float RentDeposit, float RentAmt, const string& OccupancyStatus)
{
    int storeIndex;
    bool found;

    hash(hashTable, HASH_SIZE, PropertyID, storeIndex, found, PropertyID);

    if (!found || !hashTable[storeIndex].isOccupied)
    {
        return false;
    }

    hashTable[storeIndex].PropertyAddress = PropertyAddress;
    hashTable[storeIndex].UnitDetails = UnitDetails;
    hashTable[storeIndex].RentDeposit = RentDeposit;
    hashTable[storeIndex].RentAmt = RentAmt;
    hashTable[storeIndex].OccupancyStatus = OccupancyStatus;

    return true;
}

bool Property::UnitStatus(int PropertyID, const string& OccupancyStatus)
{
    int storeIndex;
    bool found;

    hash(hashTable, HASH_SIZE, PropertyID, storeIndex, found, PropertyID);

    if(!found || !hashTable[storeIndex].isOccupied)
    {
        return false;
    }

    hashTable[storeIndex].OccupancyStatus = OccupancyStatus;
    return true;
}

const string Property::CheckVacancy(int PropertyID)
{
    int storeIndex;
    bool found;

    hash(hashTable, HASH_SIZE, PropertyID, storeIndex, found, PropertyID);

    if(!found || !hashTable[storeIndex].isOccupied)
    {
        return "Property not found. Try again!";
    }

    return hashTable[storeIndex].OccupancyStatus;
}

void Property::VacantUnits(int* vacantUnits, int& count)
{
    count = 0;

    for(int i=0; i<HASH_SIZE; i++)
    {
        if(hashTable[i].isOccupied && hashTable[i].OccupancyStatus == "empty")
        {
            vacantUnits[count++] = hashTable[i].PropertyID;
        }
    }
}

bool Property::RemoveProperty(int PropertyID)
{
    int storeIndex;
    bool found;

    hash(hashTable, HASH_SIZE, PropertyID, storeIndex, found, PropertyID);

    if(!found || !hashTable[storeIndex].isOccupied)
    {
        return false;
    }

    hashTable[storeIndex].isOccupied = false;
    hashTable[storeIndex].PropertyID = -1;
    currentSize--;
    return true;
}
