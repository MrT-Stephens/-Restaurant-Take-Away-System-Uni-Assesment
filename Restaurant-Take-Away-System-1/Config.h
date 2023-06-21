#pragma once

#include <string>

//File names and paths.
const std::string MENUITEMS_FILE_NAME = "Restaurant-System-Files/MenuItems.csv";
const std::string STAFFMEMBERS_FILE_NAME = "Restaurant-System-Files/StaffMembers.csv";
const std::string CUSTOMERS_FILE_NAME = "Restaurant-System-Files/Customers.csv";
const std::string ORDER_FILE_NAME = "Restaurant-System-Files/Orders.csv";
const std::string REPORTS_FILE_PATH = "Restaurant-System-Files/Report_.txt";

//Cusines (Can add less or more).
const std::string cuisineTypes[5] = { "Chinese", "Italian", "French", "Greek", "Indian" };

//Defined ammount for when a customer becomes a loyal customer.
const unsigned int loyalCustomerOrderNum = 20;

//For the menu item rating calculation.
const unsigned int MIN_RATING_ORDERS = 5;
const unsigned int MAX_RATING_ORDERS = 100;