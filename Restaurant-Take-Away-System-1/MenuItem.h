#pragma once

#include "Config.h"
#include <string>
#include <sstream>
#include <iomanip>

  /***************************/
 /*    'MenuItem' class.    */
/***************************/

class MenuItem
{
private:
	std::string _cuisine;
	std::string _itemName;
	unsigned int _itemAvailability;
	long double _itemPrice;
	long unsigned int _orderAmmount;
	double _rating;
public:
	MenuItem(std::string, long double, int, std::string);
	MenuItem(std::string, long double, long double, int, std::string);
	const std::string& getCuisine();
	const std::string getItemName();
	const int& getItemAvailability();
	const std::string getStrItemAvailability();
	void minusItemAvailability();
	const long double& getItemPrice();
	const std::string getStrItemPrice();
	const long unsigned int& getOrderAmmount();
	const double& getRating();
	const std::string getStrRating();
	void calcRating();
	const std::string getStrOrderAmmount();
	void addToOrderAmmount();
	std::string getAllCSVData();
};