#ifndef HOUSE_AVAILABILITY_MENU_HPP
#define HOUSE_AVAILABILITY_MENU_HPP

#include "Property.hpp"

class HouseAvailabilityMenu {
private:
    House::Property propertyManager;

    // Helper functions for menu operations
    void addNewProperty();
    void updateProperty();
    void updateStatus();
    void checkStatus();
    void viewVacantProperties();
    void removeProperty();

public:
    HouseAvailabilityMenu();
    void displayMenu();
};

#endif
