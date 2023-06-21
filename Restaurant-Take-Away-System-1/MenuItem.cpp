#include "MenuItem.h"

  /***************************************/
 /*    'MenuItem' class implemented.    */
/***************************************/

MenuItem::MenuItem(std::string cuisine, long double itemPrice, int itemAvailability, std::string itemName) :
	_cuisine(cuisine), _itemName(itemName), _itemPrice(itemPrice), _itemAvailability(itemAvailability), _orderAmmount(0) { };

MenuItem::MenuItem(std::string cuisine, long double orderAmmount, long double itemPrice, int itemAvailability, std::string itemName) :
	_cuisine(cuisine), _itemName(itemName), _itemPrice(itemPrice), _orderAmmount(orderAmmount), _itemAvailability(itemAvailability) { calcRating(); };

const std::string& MenuItem::getCuisine()
{
	return _cuisine;
}

const std::string MenuItem::getItemName()
{
	return _itemName;
}

const int& MenuItem::getItemAvailability()
{
	return _itemAvailability;
}

const long double& MenuItem::getItemPrice()
{
	return _itemPrice;
}

const long unsigned int& MenuItem::getOrderAmmount()
{
	return _orderAmmount;
}

const std::string MenuItem::getStrItemAvailability()
{
	return std::to_string(_itemAvailability);
}

const std::string MenuItem::getStrItemPrice()
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << _itemPrice;
	return ss.str();
}

const std::string MenuItem::getStrOrderAmmount()
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << _orderAmmount;
	return ss.str();
}

std::string MenuItem::getAllCSVData()
{
	std::stringstream ss;
	ss << _itemName << "," << _itemAvailability << "," << _itemPrice << "," << _orderAmmount << "," << _cuisine;
	return ss.str();
}

void MenuItem::minusItemAvailability()
{
	_itemAvailability--;
}

void MenuItem::addToOrderAmmount()
{
	_orderAmmount++;
}

const double& MenuItem::getRating()
{
	return _rating;
}

const std::string MenuItem::getStrRating()
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << _rating;
	return ss.str();
}

void MenuItem::calcRating()
{
	double tempRating = 10 * (static_cast<double>(_orderAmmount) - MIN_RATING_ORDERS) / (MAX_RATING_ORDERS - MIN_RATING_ORDERS);
	_rating = ((tempRating <= 0) ? 0 : ((tempRating >= 10) ? 10 : tempRating));
}