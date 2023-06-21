#pragma once

#include "MenuItem.h"
#include "Customer.h"
#include "StaffMember.h"

#include <string>
#include <vector>
#include <fstream>

namespace file
{
	  /***************************************************/
     /*    'FileInOut' class within 'file namespace.    */
    /***************************************************/

	class FileInOut
	{
	protected:
		std::ifstream _inFile;
		std::ofstream _outFile;
	public:
		FileInOut();
		template <class T>
		bool outputToFile(const std::string&, std::vector<T*>&, std::string(T::*)());
		bool inputMenuFile(const std::string&, std::vector<MenuItem*>&);
		bool inputCustomerFile(const std::string&, std::vector<Customer*>&);
		bool inputStaffMemberFile(const std::string&, std::vector<StaffMember*>&);
	};
}


/****************************************/
/*    'FileInOut' class implemented.    */
/****************************************/

//FileInOut constuctor.
file::FileInOut::FileInOut() { };

//Universal output to file function which can output a vector of objects for any class to a desired file.
template <class T>
bool file::FileInOut::outputToFile(const std::string& fileName, std::vector<T*>& objects, std::string(T::* get_all_object_data_func)())
{
	_outFile.open(fileName, std::ios::out);

	if (!_outFile || _outFile.fail() || objects.empty())
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			_outFile << (objects[i]->*get_all_object_data_func)() << "\n";
		}
	}
	_outFile.close();
	return true;
}

//Fucntion to input all the menu items from a desired file.
bool file::FileInOut::inputMenuFile(const std::string& fileName, std::vector<MenuItem*>& menuItems)
{
	_inFile.open(fileName, std::ios::in);

	if (!_inFile || _inFile.fail())
	{
		return false;
	}
	else
	{
		try
		{
			bool endOfFile = false;
			//Used a custom 'endOfFile' check as the usally 'eof' wasnt working for my file input implementation.
			while (!endOfFile || !_inFile.eof())
			{
				endOfFile = (_inFile.peek() == -1) ? true : false;

				//File input will get everything in as strings and covert it to the different data types needed. 
				if (!endOfFile || !_inFile.eof())
				{
					std::string line, word; std::vector<std::string> temp;
					std::getline(_inFile, line); std::stringstream ss(line);

					while (std::getline(ss, word, ','))
					{
						temp.push_back(word);
					}
					MenuItem* tempObj = new MenuItem(temp[4], std::stoi(temp[3]), std::stod(temp[2]), std::stoi(temp[1]), temp[0]);
					menuItems.push_back(tempObj);
				}
			}
		}
		catch (const std::exception& ex)    //Catches the exception if ('stoi', 'stod') fails.
		{
			return false;
		}
	}
	_inFile.close();
	return true;
}

//Fucntion to input all the customers from a desired file.
bool file::FileInOut::inputCustomerFile(const std::string& fileName, std::vector<Customer*>& customer)
{
	_inFile.open(fileName, std::ios::in);

	if (!_inFile || _inFile.fail())
	{
		return false;
	}
	else
	{
		try
		{
			bool endOfFile = false;
			//Used a custom 'endOfFile' check as the usally 'eof' wasnt working for my file input implementation.
			while (!endOfFile || !_inFile.eof())
			{
				endOfFile = (_inFile.peek() == -1) ? true : false;

				//File input will get everything in as strings and covert it to the different data types needed. 
				if (!endOfFile || !_inFile.eof())
				{
					std::string line, word; std::vector<std::string> temp; std::vector<std::string> address;
					std::getline(_inFile, line); std::stringstream ss(line);

					while (std::getline(ss, word, ','))
					{
						temp.push_back(word);
					}
					address.push_back(temp[3]); address.push_back(temp[4]); address.push_back(temp[5]);

					Customer* tempObj = new Customer(std::stoi(temp[6]), address, temp[2], temp[1], temp[0]);
					customer.push_back(tempObj);
				}
			}
		}
		catch (const std::exception& ex)    //Catches the exception if ('stoi', 'stod') fails.
		{
			return false;
		}
	}
	_inFile.close();
	return true;
}

//Fucntion to input all the staff members from a desired file.
bool file::FileInOut::inputStaffMemberFile(const std::string& fileName, std::vector<StaffMember*>& staffMembers)
{
	_inFile.open(fileName, std::ios::in);

	if (!_inFile || _inFile.fail())
	{
		return false;
	}
	else
	{
		try
		{
			bool endOfFile = false;
			//Used a custom 'endOfFile' check as the usally 'eof' wasnt working for my file input implementation.
			while (!endOfFile || !_inFile.eof())
			{
				endOfFile = (_inFile.peek() == -1) ? true : false;

				//File input will get everything in as strings and covert it to the different data types needed. 
				if (!endOfFile || !_inFile.eof())
				{
					std::string line, word; std::vector<std::string> temp; std::vector<std::string> address;
					std::getline(_inFile, line); std::stringstream ss(line);

					while (std::getline(ss, word, ','))
					{
						temp.push_back(word);
					}
					address.push_back(temp[4]); address.push_back(temp[5]); address.push_back(temp[6]);

					StaffMember* tempObj;

					if (temp[0].find("Chef") != std::string::npos)
					{
						tempObj = new Chef(temp[0], temp[8], temp[7], address, temp[3], temp[2], temp[1]);
					}
					else if (temp[0].find("Delivery Staff") != std::string::npos)
					{
						tempObj = new DeliveryStaff(temp[8], temp[7], address, temp[3], temp[2], temp[1]);
					}
					else if (temp[0].find("Manager") != std::string::npos)
					{
						tempObj = new Manager(temp[8], temp[7], address, temp[3], temp[2], temp[1]);
					}
					else if (temp[0].find("Receptionist") != std::string::npos)
					{
						tempObj = new Receptionist(temp[8], temp[7], address, temp[3], temp[2], temp[1]);
					}
					staffMembers.push_back(tempObj);
				}
			}
		}
		catch (const std::exception& ex)    //Catches the exception if anything fails.
		{
			return false;
		}
	}
	_inFile.close();
	return true;
}