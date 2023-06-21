#include "Order.h"

  /************************************/
 /*    'Order' class implemented.    */
/************************************/

Order::Order(double orderPrice, std::string typeOfOrder, std::vector<MenuItem*> menuItems, Customer* customer) :
	_orderPrice(orderPrice), _typeOfOrder(typeOfOrder), _menuItems(menuItems), _customer(customer), _timeDate(new Time()) 
{ 
	outputToOrderFile(ORDER_FILE_NAME); _customer->addToAmmountOfOrders(); 

	for (size_t i = 0; i < _menuItems.size(); i++)
	{
		_menuItems[i]->minusItemAvailability();
		_menuItems[i]->addToOrderAmmount();
	}
};

Order::~Order()
{
	delete _timeDate;

	for (size_t i = 0; i < _menuItems.size(); i++)
	{
		delete (_menuItems[i]);
	}
	_menuItems.clear();
}

Customer& Order::getCustomer()
{
	return *_customer;
}

std::vector<MenuItem*>& Order::getMenuItems()
{
	return _menuItems;
}

std::string Order::getStrMenuItems()
{
	std::stringstream ss;
	for (size_t i = 0; i < _menuItems.size(); i++)
	{
		ss << _menuItems[i]->getItemName() << ((_menuItems.size() - 1 != i) ? ", " : "");
	}
	return ss.str();
}

const std::string& Order::getTypeOfOrder()
{
	return _typeOfOrder;
}

const long double& Order::getOrderPrice()
{
	return _orderPrice;
}

const std::string Order::getCustomerName()
{
	return _customer->getFullName();
}

const std::string Order::getTimeAdded()
{
	return _timeDate->getTimeAdded();
}

const std::string Order::getStrOrderPrice()
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << "$" << _orderPrice;
	return ss.str();
}

void Order::outputToOrderFile(const std::string& fileName)
{
	std::ofstream outFile;

	outFile.open(fileName, std::ios::app);

	outFile << _customer->getFullName() << "," << _customer->getEmailAddress() << ",";

	for (size_t i = 0; i < _menuItems.size(); i++)
	{
		outFile << _menuItems[i]->getItemName() << ",£" << _menuItems[i]->getItemPrice() << ",";
	}

	outFile << _typeOfOrder << ",£" << _orderPrice << "," << _timeDate->getTimeAdded() << "," << _timeDate->getDateAdded() << "\n";

	outFile.close();
}