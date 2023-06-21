#pragma once

#include "Time.h"
#include <string>
#include <vector>
#include <sstream>
#include <time.h>

  /*****************************/
 /*    'StaffMember' Class    */
/*****************************/

class StaffMember
{
protected:
	std::string _firstName;
	std::string _lastName;
	std::string _phoneNumber;
	std::vector<std::string> _address;
	Time* _timeDate;
public:
	StaffMember(const std::vector<std::string>&, const std::string&, const std::string&, const std::string&);
	StaffMember(const std::string&, const std::string&, const std::vector<std::string>&, const std::string&, const std::string&, const std::string&);
	~StaffMember();

	std::string getFullName();
	const std::string& getFirstName();
	const std::string& getLastName();
	const std::string& getPhoneNumber();
	const std::vector<std::string>& getAddress();
	const std::string& getAddressLineOne();
	const std::string& getCity();
	const std::string& getPostCode();
	const std::string getTimeAdded();
	const std::string getDateAdded();

	virtual std::string getStaffRank() = 0;
	virtual std::string getAllCSVData();
};

  /**********************/
 /*    'Chef' Class    */
/**********************/

class Chef : public StaffMember
{
private:
	std::string _chefRank;
public:
	Chef(std::string, std::vector<std::string>, std::string, std::string, std::string);
	Chef(std::string, std::string, std::string, std::vector<std::string>, std::string, std::string, std::string);

	std::string getStaffRank();
	std::string getAllCSVData() override;
};

  /*******************************/
 /*    'DeliveryStaff' Class    */
/*******************************/

class DeliveryStaff : public StaffMember
{
public:
	DeliveryStaff(std::vector<std::string>, std::string, std::string, std::string);
	DeliveryStaff(std::string, std::string, std::vector<std::string>, std::string, std::string, std::string);

	std::string getStaffRank();
	std::string getAllCSVData() override;
};

  /*************************/
 /*    'Manager' Class    */
/*************************/

class Manager : public StaffMember
{
public:
	Manager(std::vector<std::string>, std::string, std::string, std::string);
	Manager(std::string, std::string, std::vector<std::string>, std::string, std::string, std::string);

	std::string getStaffRank();
	std::string getAllCSVData() override;
};

  /******************************/
 /*    'Receptionist' Class    */
/******************************/

class Receptionist : public StaffMember
{
public:
	Receptionist(std::vector<std::string>, std::string, std::string, std::string);
	Receptionist(std::string, std::string, std::vector<std::string>, std::string, std::string, std::string);

	std::string getStaffRank();
	std::string getAllCSVData() override;
};