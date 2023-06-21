#include "Customer.h"

  /***************************************/
 /*    'Customer' class implemented.    */
/***************************************/

Customer::Customer(std::vector<std::string> address, std::string emailAddress, std::string lastName, std::string firstName) :
	_firstName(firstName), _lastName(lastName), _emailAddress(emailAddress), _address(address) { };

Customer::Customer(unsigned long int ammountOfOrders, std::vector<std::string> address, std::string emailAddress, std::string lastName, std::string firstName) :
	_firstName(firstName), _lastName(lastName), _emailAddress(emailAddress), _address(address), _ammountOfOrders(ammountOfOrders) 
{
	_loyalCustomer = (_ammountOfOrders >= loyalCustomerOrderNum) ? true : false;
};

std::string Customer::getFullName()
{
	std::string temp(_firstName);
	temp.insert(temp.size(), " ");
	temp.insert(temp.size(), _lastName);
	return temp;
}

const std::string& Customer::getFirstName()
{
	return _firstName;
}

const std::string& Customer::getLastName()
{
	return _lastName;
}

const std::string& Customer::getEmailAddress()
{
	return _emailAddress;
}

const std::vector<std::string>& Customer::getAddress()
{
	return _address;
}

const std::string& Customer::getAddressLineOne()
{
	return _address[0];
}

const std::string& Customer::getCity()
{
	return _address[1];
}

const std::string& Customer::getPostCode()
{
	return _address[2];
}

const unsigned long int& Customer::getAmmountOfOrders()
{
	return _ammountOfOrders;
}

const std::string Customer::getStrAmmountOfOrders()
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << _ammountOfOrders;
	return ss.str();
}

void Customer::addToAmmountOfOrders()
{
	_ammountOfOrders++;
}

const bool& Customer::getLoyalCustomer()
{
	return _loyalCustomer;
}

const std::string Customer::getStrLoyalCustomer()
{
	return ((_loyalCustomer) ? "True" : "False");
}

std::string Customer::getAllCSVData()
{
	std::stringstream ss;
	ss << _firstName << "," << _lastName << "," << _emailAddress;

	for (size_t i = 0; i < _address.size(); i++)
	{
		ss << "," << _address[i];
	}
	ss << "," << _ammountOfOrders;
	return ss.str();
}
