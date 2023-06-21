#pragma once

#include "Config.h"
#include "Time.h"
#include "MenuItem.h"
#include "Customer.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

  /************************/
 /*    'Order' class.    */
/************************/

class Order
{
private:
	Customer* _customer;
	std::vector<MenuItem*> _menuItems;
	std::string _typeOfOrder;
	long double _orderPrice;
	Time* _timeDate;
public:
	Order(double, std::string, std::vector<MenuItem*>, Customer*);
	~Order();

	Customer& getCustomer();
	std::vector<MenuItem*>& getMenuItems();
	std::string getStrMenuItems();
	const std::string getCustomerName();
	const std::string& getTypeOfOrder();
	const long double& getOrderPrice();
	const std::string getStrOrderPrice();
	const std::string getTimeAdded();
	void outputToOrderFile(const std::string&);
};
