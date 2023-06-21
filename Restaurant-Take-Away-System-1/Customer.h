#pragma once

#include "Config.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

  /***************************/
 /*    'Customer' class.    */
/***************************/

class Customer
{
private:
	std::string _firstName;
	std::string _lastName;
	std::string _emailAddress;
	std::vector<std::string> _address;
	unsigned long int _ammountOfOrders;
	bool _loyalCustomer;
public:
	Customer(std::vector<std::string>, std::string, std::string, std::string);
	Customer(unsigned long int, std::vector<std::string>, std::string, std::string, std::string);

	std::string getFullName();
	const std::string& getFirstName();
	const std::string& getLastName();
	const std::string& getEmailAddress();
	const std::vector<std::string>& getAddress();
	const std::string& getAddressLineOne();
	const std::string& getCity();
	const std::string& getPostCode();
	const bool& getLoyalCustomer();
	const std::string getStrLoyalCustomer();
	const unsigned long int& getAmmountOfOrders();
	const std::string getStrAmmountOfOrders();
	void addToAmmountOfOrders();
	std::string getAllCSVData();
};