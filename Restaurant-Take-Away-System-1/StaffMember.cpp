#include "StaffMember.h"

  /******************************************/
 /*    'StaffMember' Class implemented.    */
/******************************************/

StaffMember::StaffMember(const std::vector<std::string>& address, const std::string& phoneNumber, const std::string& lastName, const std::string& firstName) :
	_address(address), _phoneNumber(phoneNumber), _lastName(lastName), _firstName(firstName), _timeDate(new Time()) { };

StaffMember::StaffMember(const std::string& dateAdded, const std::string& timeAdded, const std::vector<std::string>& address, const std::string& phoneNumber, const std::string& lastName, const std::string& firstName) :
	_timeDate(new Time(timeAdded, dateAdded)), _address(address), _phoneNumber(phoneNumber), _lastName(lastName), _firstName(firstName) { };

StaffMember::~StaffMember() { delete _timeDate; };

std::string StaffMember::getFullName()
{
	std::string temp(_firstName);
	temp.insert(temp.size(), " ");
	temp.insert(temp.size(), _lastName);
	return temp;
}

const std::string& StaffMember::getFirstName()
{
	return _firstName;
}

const std::string& StaffMember::getLastName()
{
	return _lastName;
}

const std::string& StaffMember::getPhoneNumber()
{
	return _phoneNumber;
}

const std::vector<std::string>& StaffMember::getAddress()
{
	return _address;
}

const std::string& StaffMember::getAddressLineOne()
{
	return _address[0];
}

const std::string& StaffMember::getCity()
{
	return _address[1];
}

const std::string& StaffMember::getPostCode()
{
	return _address[2];
}

const std::string StaffMember::getTimeAdded()
{
	return _timeDate->getTimeAdded();
}

const std::string StaffMember::getDateAdded()
{
	return _timeDate->getDateAdded();

}

std::string StaffMember::getAllCSVData()
{
	std::stringstream ss;
	ss << _firstName << "," << _lastName << "," << _phoneNumber << ",";

	for (size_t i = 0; i < _address.size(); i++)
	{
		ss << _address[i] << ",";
	}
	ss << _timeDate->getTimeAdded() << "," << _timeDate->getDateAdded();

	return ss.str();
}

  /***********************************/
 /*    'Chef' Class implemented.    */
/***********************************/

Chef::Chef(std::string cuisineType, std::vector<std::string> address, std::string phoneNumber, std::string lastName, std::string firstName) :
	StaffMember(address, phoneNumber, lastName, firstName), _chefRank("Chef - " + cuisineType) { };

Chef::Chef(std::string cuisineType, std::string dateAdded, std::string timeAdded, std::vector<std::string> address, std::string phoneNumber, std::string lastName, std::string firstName) :
	StaffMember(dateAdded, timeAdded, address, phoneNumber, lastName, firstName), _chefRank(cuisineType) { };

std::string Chef::getStaffRank()
{
	return _chefRank;
}

std::string Chef::getAllCSVData()
{
	std::stringstream ss;
	ss << _chefRank << "," << _firstName << "," << _lastName << "," << _phoneNumber << ",";

	for (size_t i = 0; i < _address.size(); i++)
	{
		ss << _address[i] << ",";
	}
	ss << _timeDate->getTimeAdded() << "," << _timeDate->getDateAdded();

	return ss.str();
}

  /********************************************/
 /*    'DeliveryStaff' Class implemented.    */
/********************************************/

DeliveryStaff::DeliveryStaff(std::vector<std::string> address, std::string phoneNumber, std::string lastName, std::string firstName) :
	StaffMember(address, phoneNumber, lastName, firstName) { };

DeliveryStaff::DeliveryStaff(std::string dateAdded, std::string timeAdded, std::vector<std::string> address, std::string phoneNumber, std::string lastName, std::string firstName) :
	StaffMember(dateAdded, timeAdded, address, phoneNumber, lastName, firstName) { };

std::string DeliveryStaff::getStaffRank()
{
	return "Delivery Staff";
}

std::string DeliveryStaff::getAllCSVData()
{
	std::stringstream ss;
	ss << "Delivery Staff" << "," << _firstName << "," << _lastName << "," << _phoneNumber << ",";

	for (size_t i = 0; i < _address.size(); i++)
	{
		ss << _address[i] << ",";
	}
	ss << _timeDate->getTimeAdded() << "," << _timeDate->getDateAdded();

	return ss.str();
}

  /**************************************/
 /*    'Manager' Class implemented.    */
/**************************************/

Manager::Manager(std::vector<std::string> address, std::string phoneNumber, std::string lastName, std::string firstName) :
	StaffMember(address, phoneNumber, lastName, firstName) { };

Manager::Manager(std::string dateAdded, std::string timeAdded, std::vector<std::string> address, std::string phoneNumber, std::string lastName, std::string firstName) :
	StaffMember(dateAdded, timeAdded, address, phoneNumber, lastName, firstName) { };

std::string Manager::getStaffRank()
{
	return "Manager";
}

std::string Manager::getAllCSVData()
{
	std::stringstream ss;
	ss << "Manager" << "," << _firstName << "," << _lastName << "," << _phoneNumber << ",";

	for (size_t i = 0; i < _address.size(); i++)
	{
		ss << _address[i] << ",";
	}
	ss << _timeDate->getTimeAdded() << "," << _timeDate->getDateAdded();

	return ss.str();
}

  /*******************************************/
 /*    'Receptionist' Class implemented.    */
/*******************************************/

Receptionist::Receptionist(std::vector<std::string> address, std::string phoneNumber, std::string lastName, std::string firstName) :
	StaffMember(address, phoneNumber, lastName, firstName) { };

Receptionist::Receptionist(std::string dateAdded, std::string timeAdded, std::vector<std::string> address, std::string phoneNumber, std::string lastName, std::string firstName) :
	StaffMember(dateAdded, timeAdded, address, phoneNumber, lastName, firstName) { };

std::string Receptionist::getStaffRank()
{
	return "Receptionist";
}

std::string Receptionist::getAllCSVData()
{
	std::stringstream ss;
	ss << "Receptionist" << "," << _firstName << "," << _lastName << "," << _phoneNumber << ",";

	for (size_t i = 0; i < _address.size(); i++)
	{
		ss << _address[i] << ",";
	}
	ss << _timeDate->getTimeAdded() << "," << _timeDate->getDateAdded();

	return ss.str();
}