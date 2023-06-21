#include "MenuItem.h"
#include "Order.h"
#include "StaffMember.h"
#include "gui.h"
#include "FileInOut.h"

#include <vector>
#include <string>

  /***********************************/
 /*    'RestaurantSystem' class.    */
/***********************************/

class RestaurantSystem
{
private:
	std::vector<MenuItem*> _menuItems;
	std::vector<Customer*> _customers;
	std::vector<Order*> _orders;
	std::vector<Order*> _oldOrders;
	std::vector<StaffMember*> _staffMembers;
public:
	RestaurantSystem();
	~RestaurantSystem();
	template <typename T, typename R>
	size_t objectSearch(const std::string&, std::vector<T*>&, R(T::*)());
	template <typename T, typename R>
	std::vector<T*> objectSort(std::vector<T*>, R(T::*)(), bool);
	void initSystem();
	void printMainMenu(const std::string&);
	void staffPortalMenu();
	void customerPortalMenu();
	void outputAlldata();
	void ordersPortalMenu();
	void createOrder();
	void menuItemsPortal();
	void displayOrders();
	void deleteAnOrder();
	void addStaffMember();
	void generateReport();
	void deleteStaffMember();
	void listStaffMembers();
	void addCustomer();
	void deleteCustomer();
	void listCustomers();
	void addChef();
	void addDeliveryStaff();
	void addManager();
	void addReceptionist();
	void addMenuItem();
	void deleteMenuItem();
	void listMenuItems();
	std::string getCuisineType();
};

//Setting the base effects for the console. Format is (Main effects, secondary effects, error effects).
gui::ConsoleAffects affects({ gui::affects::bold, gui::colour::magentaForeground }, { gui::affects::bold, gui::colour::yellowForeground }, { gui::affects::bold, gui::colour::redBackground, gui::colour::whiteForeground }, true);

int main()
{
	RestaurantSystem main;    //Creates a 'RestaurantSystem' object which starts the whole program.
}

  /***********************************************/
 /*    'RestaurantSystem' class implemented.    */
/***********************************************/

//RestaurantSystem construtor and deconstuctor.
RestaurantSystem::RestaurantSystem() { initSystem(); };

RestaurantSystem::~RestaurantSystem()
{
	for (size_t i = 0; i < _menuItems.size(); i++)
	{
		delete (_menuItems[i]);
	}
	_menuItems.clear();

	for (size_t i = 0; i < _customers.size(); i++)
	{
		delete (_customers[i]);
	}
	_customers.clear();

	for (size_t i = 0; i < _orders.size(); i++)
	{
		delete (_orders[i]);
	}
	_orders.clear();

	for (size_t i = 0; i < _oldOrders.size(); i++)
	{
		delete (_oldOrders[i]);
	}
	_oldOrders.clear();

	for (size_t i = 0; i < _staffMembers.size(); i++)
	{
		delete (_staffMembers[i]);
	}
	_staffMembers.clear();
};

//initSystem function. Will attempt to pull in all the data from the files.
void RestaurantSystem::initSystem()
{
	file::FileInOut* fileIn = new file::FileInOut(); unsigned int count = 0;
	if (fileIn->inputCustomerFile(CUSTOMERS_FILE_NAME, _customers))
	{
		count++;
	}
	if (fileIn->inputMenuFile(MENUITEMS_FILE_NAME, _menuItems))
	{
		count++;
	}
	if (fileIn->inputStaffMemberFile(STAFFMEMBERS_FILE_NAME, _staffMembers))
	{
		count++;
	}
	std::string fileInfo = "* "; fileInfo.insert(fileInfo.size(), std::to_string(count)); fileInfo.insert(fileInfo.size(), "/3 Files were successfully inputted!");
	delete fileIn; printMainMenu(fileInfo);
}

//Prints the main menu to the console.
void RestaurantSystem::printMainMenu(const std::string& fileInfo)
{
	while (1)    //Infinate loop until the program is exited as the application doesnt need to go any futher back.
	{
		gui::Menu mainMenu(affects);
		mainMenu.addTitle("Restaurant Take-away system!");
		mainMenu.addDescription(fileInfo);
		mainMenu.addChoice("Exit System!");
		mainMenu.addChoice("Staff Portal!");
		mainMenu.addChoice("Customer Portal!");
		mainMenu.addChoice("Orders Portal!");
		mainMenu.addChoice("Menu Items Portal!");
		mainMenu.addChoice("Generate Report for day!");
		mainMenu.addChoice("Save all data to file!");

		switch (mainMenu.startMenu()) {    //Calls all other functions from this switch statment.
		case 0:
			outputAlldata();
			exit(0);
			break;
		case 1:
			staffPortalMenu();
			break;
		case 2:
			customerPortalMenu();
			break;
		case 3:
			ordersPortalMenu();
			break;
		case 4:
			menuItemsPortal();
			break;
		case 5:
			generateReport();
			break;
		case 6:
			outputAlldata();
			break;
		}
	}
}

//Outputs all the data within the application to the files.
void RestaurantSystem::outputAlldata()
{
	file::FileInOut* fileOut = new file::FileInOut();
	fileOut->outputToFile(CUSTOMERS_FILE_NAME, _customers, &Customer::getAllCSVData);
	fileOut->outputToFile(STAFFMEMBERS_FILE_NAME, _staffMembers, &StaffMember::getAllCSVData);
	fileOut->outputToFile(MENUITEMS_FILE_NAME, _menuItems, &MenuItem::getAllCSVData);
	delete fileOut;
}

//Prints the staff portal menu.
void RestaurantSystem::staffPortalMenu()
{
	bool goBack = false;
	while (!goBack)
	{
		gui::Menu staffMenu(affects);
		staffMenu.addTitle("Staff Portal!");
		staffMenu.addDescription("* Staff Portal has useful tools for staff members.");
		staffMenu.addChoice("Go Back!");
		staffMenu.addChoice("Add Staff Members!");
		staffMenu.addChoice("Delete Staff Member!");
		staffMenu.addChoice("List Staff Members!");

		switch (staffMenu.startMenu())
		{
		case 0:
			goBack = true;
			break;
		case 1:
			addStaffMember();
			break;
		case 2:
			deleteStaffMember();
			break;
		case 3:
			listStaffMembers();
			break;
		}
	}
}

//Prints the customer portal menu.
void RestaurantSystem::customerPortalMenu()
{
	bool goBack = false;
	while (!goBack)
	{
		gui::Menu customerMenu(affects);

		customerMenu.addTitle("Customer Portal!");
		customerMenu.addDescription("* Customer Portal has useful tools for customers.");
		customerMenu.addChoice("Go Back!");
		customerMenu.addChoice("Add Customers!");
		customerMenu.addChoice("Delete Customers!");
		customerMenu.addChoice("List Customers!");

		switch (customerMenu.startMenu())
		{
		case 0:
			goBack = true;
			break;
		case 1:
			addCustomer();
			break;
		case 2:
			deleteCustomer();
			break;
		case 3:
			listCustomers();
			break;
		}
	}
}

//Prints the orders portal menu.
void RestaurantSystem::ordersPortalMenu()
{
	bool goBack = false;
	while (!goBack)
	{
		std::string orderMsg("* Currently "); orderMsg.insert(orderMsg.size(), std::to_string(_orders.size())); orderMsg.insert(orderMsg.size(), " orders are in progress.");
		gui::Menu orderMenu(affects);

		orderMenu.addTitle("Orders Portal!");
		orderMenu.addDescription(orderMsg);
		orderMenu.addChoice("Go Back!");
		orderMenu.addChoice("Create Order!");
		orderMenu.addChoice("Complete Order!");
		orderMenu.addChoice("List Orders!");

		switch (orderMenu.startMenu())
		{
		case 0:
			goBack = true;
			break;
		case 1:
			createOrder();
			break;
		case 2:
			deleteAnOrder();
			break;
		case 3:
			displayOrders();
			break;
		}
	}
}

//Gets all the infomation to allow an order to be created.
void RestaurantSystem::createOrder()
{
	gui::MultiUserInput* orderInput = new gui::MultiUserInput(affects, "Would you like to place an order for a new customer (Y) or existing customer (N)?");
	size_t searchIndex = 0; char yesOrNo = orderInput->addYesOrNoField("Enter 'Y' or 'N'!");

	if (std::toupper(yesOrNo) == 'N')    //Exsiting customer section.
	{
		std::string tempFirstName = orderInput->addFirstNameField("First Name:");
		std::string tempLastName = orderInput->addLastNameField("Last Name:");

		searchIndex = objectSearch(tempFirstName + " " + tempLastName, _customers, &Customer::getFullName);    //Searches for the desired customer within the vector of customers.

		if (searchIndex != -1)
		{
			std::string tempMsg("Customer found at index "); tempMsg.insert(tempMsg.size(), std::to_string(searchIndex + 1)); tempMsg.push_back('!');
			gui::nextLine(1); gui::printText(tempMsg, *affects._secondaryAffects); gui::nextLine(1); std::this_thread::sleep_for(std::chrono::seconds(2)); gui::nextLine(1);
		}
		else if (searchIndex == -1)
		{
			gui::nextLine(1); gui::printText("CUSTOMER NOT FOUND!", *affects._errorAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));
			return;
		}
	}
	else if (std::toupper(yesOrNo) == 'Y')    //New customer section.
	{
		gui::nextLine(1); addCustomer(); searchIndex = _customers.size() - 1;
	}

	//Prints the menuItems to the console using the table function.
	gui::Table menuItemsTable(affects);
	menuItemsTable.addColumn("Item Name", 40, _menuItems, &MenuItem::getItemName);
	menuItemsTable.addColumn("Quantity", 10, _menuItems, &MenuItem::getStrItemAvailability);
	menuItemsTable.addColumn("Cuisine", 15, _menuItems, &MenuItem::getCuisine);
	menuItemsTable.addColumn("Price", 10, _menuItems, &MenuItem::getStrItemPrice);
	menuItemsTable.addColumn("Orders", 10, _menuItems, &MenuItem::getStrOrderAmmount);
	menuItemsTable.addColumn("Rating 0-10", 11, _menuItems, &MenuItem::getStrRating);
	menuItemsTable.printTable();

	std::vector<MenuItem*> menuItems; std::vector<unsigned int> menuItemsIndex(orderInput->addMultiIntegerField("Menu Items (Spaces between each one):", 1, _menuItems.size()));

	for (size_t i = 0; i < menuItemsIndex.size(); i++)
	{
		menuItems.push_back(_menuItems[menuItemsIndex[i] - 1]);    //Loops through and copies all the menuItems pointers that the user picks.
	}

	std::string collectOrDelivery = ((std::toupper(orderInput->addYesOrNoField("Would you like to collect (Y) or delivery (N):")) == 'Y') ? "In-person" : "Delivery");
	double orderTotal = 0;

	for (size_t i = 0; i < menuItems.size(); i++)
	{
		orderTotal += menuItems[i]->getItemPrice();    //Calculates the orders total price.
	}

	_orders.push_back(new Order(orderTotal, collectOrDelivery, menuItems, _customers[searchIndex]));    //Appends the new order to the back of the orders vector.

	gui::nextLine(1); gui::printText("Order has been created please go to list orders to see it!", *affects._secondaryAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));
}

//Allows the user to delete an order.
void RestaurantSystem::deleteAnOrder()
{
	try
	{
		if (_orders.size() >= 1)
		{
			size_t size = _orders[0]->getStrMenuItems().size();
			for (size_t i = 0; i < _orders.size(); i++)
			{
				if (_orders[i]->getStrMenuItems().size() > size)
				{
					size = _orders[i]->getStrMenuItems().size();
				}
			}

			gui::Table ordersTable(affects);
			ordersTable.addColumn("Customer", 35, _orders, &Order::getCustomerName);
			ordersTable.addColumn("Price", 7, _orders, &Order::getStrOrderPrice);
			ordersTable.addColumn("Type Of Order", 13, _orders, &Order::getTypeOfOrder);
			ordersTable.addColumn("Menu Items", size + 5, _orders, &Order::getStrMenuItems);
			ordersTable.addColumn("Time Taken", 10, _orders, &Order::getTimeAdded);
			ordersTable.printTable();

			gui::MultiUserInput* completeOrderIndput = new gui::MultiUserInput(affects, "Please type the customers order number!");

			gui::consoleIgnore('\n'); std::vector<unsigned int> ordersIndex(completeOrderIndput->addMultiIntegerField("Order Numbers (Spaces between each one):", 1, _orders.size()));

			for (size_t i = 0; i < ordersIndex.size(); i++)
			{
				_oldOrders.push_back(std::move(_orders[ordersIndex[i] - 1]));
				std::swap(_orders[_orders.size() - 1], _orders[ordersIndex[i] - 1]); _orders.pop_back();
			}

			gui::nextLine(1); gui::printText("Order has been completed!", *affects._secondaryAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));

			delete completeOrderIndput;
			return;
		}
		if (_orders.size() < 1)
		{
			gui::printText("NO ORDERS HAVE BEEN CREATED!", *affects._errorAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));
			return;
		}
	} 
	catch (const std::exception& ex)
	{
		gui::nextLine(1); gui::printText(ex.what(), *affects._secondaryAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

//generates the day report.
void RestaurantSystem::generateReport()
{
	size_t totalNoOrders = _orders.size() + _oldOrders.size(); long double totalIncome = 0;
	std::string mostPopularCuisine; std::string mostPopularMenuItem; std::string mostLoyalCustomer;

	for (size_t i = 0; i < _orders.size(); i++)    //Calculates the ammount sold for that day.
	{
		totalIncome += _orders[i]->getOrderPrice();
	}

	for (size_t i = 0; i < _oldOrders.size(); i++)    //Calculates the ammount sold for that day.
	{
		totalIncome += _oldOrders[i]->getOrderPrice();    //totalIncome = totalIncome + 
	}

	size_t cusineOrders[sizeof(cuisineTypes) / sizeof(cuisineTypes[0])] = { 0 };
	for (size_t i0 = 0; i0 < (sizeof(cuisineTypes) / sizeof(cuisineTypes[0])); i0++)    //Adds up the total ammount of orders per cuisine.
	{
		for (size_t i1 = 0; i1 < _menuItems.size(); i1++)
		{
			if (_menuItems[i1]->getCuisine() == cuisineTypes[i0])
			{
				cusineOrders[i0] += _menuItems[i1]->getOrderAmmount();
			}
		}
	}

	size_t tempCusineOrders = cusineOrders[0];
	mostPopularCuisine = cuisineTypes[0];
	for (size_t i = 0; i < (sizeof(cuisineTypes) / sizeof(cuisineTypes[0])); i++)    //Finds the most popular cuisine.
	{
		if (cusineOrders[i] > tempCusineOrders)
		{
			tempCusineOrders = cusineOrders[i];
			mostPopularCuisine = cuisineTypes[i];
		}
	}

	unsigned int tempOrderAmmount = _menuItems[0]->getOrderAmmount();
	mostPopularMenuItem = _menuItems[0]->getItemName();
	for (size_t i = 0; i < _menuItems.size(); i++)    //Finds the most popualar menu item.
	{
		if (_menuItems[i]->getOrderAmmount() > tempOrderAmmount)
		{
			tempOrderAmmount = _menuItems[i]->getOrderAmmount();
			mostPopularMenuItem = _menuItems[i]->getItemName();
		}
	}

	unsigned int tempCustomerOrder = _customers[0]->getAmmountOfOrders();
	for (size_t i = 0; i < _customers.size(); i++)    //Finds the most popular customer.
	{
		if (_customers[i]->getAmmountOfOrders() > tempCustomerOrder)
		{
			tempCustomerOrder = _customers[i]->getAmmountOfOrders();
			mostLoyalCustomer = _customers[i]->getFullName();
		}
	}

	//Prints the report to the console using the 'printText' from 'gui' namespace.
	gui::printText("Report for the day!", gui::affects::underline + *affects._mainAffects); gui::nextLine(2);
	gui::printText("\t* Total no of orders that have been booked: ", *affects._mainAffects);
	gui::printText(std::to_string(totalNoOrders), *affects._secondaryAffects); gui::nextLine(1);
	gui::printText("\t* Total income for the day: ", *affects._mainAffects); 
	gui::printText("$" + std::to_string(totalIncome), *affects._secondaryAffects); gui::nextLine(1);
	gui::printText("\t* Most popular cuisine: ", *affects._mainAffects); 
	gui::printText(mostPopularCuisine, *affects._secondaryAffects); gui::nextLine(1);
	gui::printText("\t* Most popular item from the menu: ", *affects._mainAffects); 
	gui::printText(mostPopularMenuItem, *affects._secondaryAffects); gui::nextLine(1);
	gui::printText("\t* Most loyal customers: ", *affects._mainAffects); 
	gui::printText(mostLoyalCustomer, *affects._secondaryAffects); gui::nextLine(2);

	//Outputs the report to the file with the current date in the name.
	Time currentTime; std::ofstream outReport; std::string reportFile(REPORTS_FILE_PATH); reportFile.insert(31, currentTime.getDateStringDash()); outReport.open(reportFile, std::ios::out);
	outReport << "Report for the day!\n" << "\t* Total no of orders that have been booked: " << totalNoOrders << "\n\t* Total income for the day: $" << totalIncome << "\n\t* Most popular cuisine: "
		<< mostPopularCuisine << "\n\t* Most popular item from the menu: " << mostPopularMenuItem << "\n\t* Most loyal customers: " << mostLoyalCustomer; outReport.close();

	//Pauses the console.
	gui::consolePause(*affects._mainAffects);
}

//Prints the menu items portal menu.
void RestaurantSystem::menuItemsPortal()
{
	bool goBack = false;
	while (!goBack)
	{
		gui::Menu menuItemsMenu(affects);

		menuItemsMenu.addTitle("Menu Itmes Portal!");
		menuItemsMenu.addDescription("* Menu Items Portal has useful tools for dealing wiht the menu items.");
		menuItemsMenu.addChoice("Go Back!");
		menuItemsMenu.addChoice("Add an menu item!");
		menuItemsMenu.addChoice("Delete menu item!");
		menuItemsMenu.addChoice("List menu items!");

		switch (menuItemsMenu.startMenu())
		{
		case 0:
			goBack = true;
			break;
		case 1:
			addMenuItem();
			break;
		case 2:
			deleteMenuItem();
			break;
		case 3:
			listMenuItems();
			break;
		}
	}
}

//Allows the user to add a new menu item.
void RestaurantSystem::addMenuItem()
{
	gui::MultiUserInput* menuItemInput = new gui::MultiUserInput(affects, "Add Menu Item!");
	MenuItem* tempMenuItem = new MenuItem(getCuisineType(), menuItemInput->addMoneyInput("Item Price:", '$'), menuItemInput->addIntegerField("Item Avaliability:"), menuItemInput->addRandomCharWithCapitalField("Item Name:"));
	_menuItems.push_back(tempMenuItem);
	delete menuItemInput, tempMenuItem;
}

//Allows the user to delete a menu item.
void RestaurantSystem::deleteMenuItem()
{
	gui::MultiUserInput* deleteMenuItemInput = new gui::MultiUserInput(affects, "Delete Menu Item!");
	std::string tempItemName = deleteMenuItemInput->addRandomCharWithCapitalField("Item Name:");

	size_t index = objectSearch(tempItemName, _menuItems, &MenuItem::getItemName);

	if (index != -1)
	{
		std::string tempMsg("Menu Item found at index "); tempMsg.insert(tempMsg.size(), std::to_string(index + 1)); tempMsg.push_back('!');
		gui::nextLine(1); gui::printText(tempMsg, *affects._secondaryAffects); gui::nextLine(1); std::this_thread::sleep_for(std::chrono::seconds(2));

		std::swap(_menuItems[_menuItems.size() - 1], _menuItems[index]); _menuItems.pop_back();

		gui::nextLine(1); gui::printText("Sucessfully deleted menu item!", *affects._secondaryAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	else if (index == -1)
	{
		gui::nextLine(1); gui::printText("MENU ITEM NOT FOUND!", *affects._errorAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	delete deleteMenuItemInput;
}

//Prints all the menu items to the console in a table.
void RestaurantSystem::listMenuItems()
{
	gui::Table menuItemsTable(affects);

	menuItemsTable.addColumn("Item Name", 40, _menuItems, &MenuItem::getItemName);
	menuItemsTable.addColumn("Quantity", 10, _menuItems, &MenuItem::getStrItemAvailability);
	menuItemsTable.addColumn("Cuisine", 15, _menuItems, &MenuItem::getCuisine);
	menuItemsTable.addColumn("Price", 10, _menuItems, &MenuItem::getStrItemPrice);
	menuItemsTable.addColumn("Orders", 10, _menuItems, &MenuItem::getStrOrderAmmount);
	menuItemsTable.addColumn("Rating 0-10", 11, _menuItems, &MenuItem::getStrRating);
	menuItemsTable.printTable();

	gui::consolePause(*affects._mainAffects);
}

//Prints all the orders to the console in a table.
void RestaurantSystem::displayOrders()
{
	try
	{
		if (_orders.size() >= 1)
		{
			size_t size = _orders[0]->getStrMenuItems().size();
			for (size_t i = 0; i < _orders.size(); i++)
			{
				if (_orders[i]->getStrMenuItems().size() > size)
				{
					size = _orders[i]->getStrMenuItems().size();
				}
			}

			gui::Table ordersTable(affects);

			ordersTable.addColumn("Customer", 35, _orders, &Order::getCustomerName);
			ordersTable.addColumn("Price", 7, _orders, &Order::getStrOrderPrice);
			ordersTable.addColumn("Type Of Order", 13, _orders, &Order::getTypeOfOrder);
			ordersTable.addColumn("Menu Items", size + 5, _orders, &Order::getStrMenuItems);
			ordersTable.addColumn("Time Taken", 10, _orders, &Order::getTimeAdded);
			ordersTable.printTable();

			gui::consolePause(*affects._mainAffects);
			return;
		}
		if (_orders.size() < 1)
		{
			gui::printText("NO ORDERS HAVE BEEN CREATED!", *affects._errorAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));
			return;
		}
	}
	catch (const std::exception& ex)
	{
		gui::nextLine(1); gui::printText(ex.what(), *affects._errorAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

//Allows the user to add a new staff member.
void RestaurantSystem::addStaffMember()
{
	gui::Menu addStaffMember(affects);
	addStaffMember.addTitle("Add Staff Member!");
	addStaffMember.addDescription("Which Staff Member would you like to add.");
	addStaffMember.addChoice("Add Chef!");
	addStaffMember.addChoice("Add Delivery Staff!");
	addStaffMember.addChoice("Add Manager!");
	addStaffMember.addChoice("Add Receptionist!");

	switch (addStaffMember.startMenu())
	{
	case 0:
		addChef();
		break;
	case 1:
		addDeliveryStaff();
		break;
	case 2:
		addManager();
		break;
	case 3:
		addReceptionist();
		break;
	}
}

//Allows the user to add a new chef.
void RestaurantSystem::addChef()
{
	gui::MultiUserInput* chefInput = new gui::MultiUserInput(affects, "Add New Staff Member!");
	StaffMember* tempChef = new Chef(getCuisineType(), chefInput->addAdressField(), chefInput->addPhoneNumberField("Phone Number:"), chefInput->addLastNameField("Last Name:"), chefInput->addFirstNameField("First Name:"));
	_staffMembers.push_back(tempChef);
	delete chefInput, tempChef;
}

//Allows the user to add a new delivery staff.
void RestaurantSystem::addDeliveryStaff()
{
	gui::MultiUserInput* deliveryInput = new gui::MultiUserInput(affects, "Add New Staff Member!");
	StaffMember* tempDeliveryStaff = new DeliveryStaff(deliveryInput->addAdressField(), deliveryInput->addPhoneNumberField("Phone Number:"), deliveryInput->addLastNameField("Last Name:"), deliveryInput->addFirstNameField("First Name:"));
	_staffMembers.push_back(tempDeliveryStaff);
	delete deliveryInput, tempDeliveryStaff;
}

//Allows the user to add a new manager.
void RestaurantSystem::addManager()
{
	gui::MultiUserInput* managerInput = new gui::MultiUserInput(affects, "Add New Staff Member!");
	StaffMember* tempManager = new Manager(managerInput->addAdressField(), managerInput->addPhoneNumberField("Phone Number:"), managerInput->addLastNameField("Last Name:"), managerInput->addFirstNameField("First Name:"));
	_staffMembers.push_back(tempManager);
	delete managerInput, tempManager;
}

//Allows the user to add a new receptionist.
void RestaurantSystem::addReceptionist()
{
	gui::MultiUserInput* receptionistInput = new gui::MultiUserInput(affects, "Add New Staff Member!");
	StaffMember* tempReceptionist = new Receptionist(receptionistInput->addAdressField(), receptionistInput->addPhoneNumberField("Phone Number:"), receptionistInput->addLastNameField("Last Name:"), receptionistInput->addFirstNameField("First Name:"));
	_staffMembers.push_back(tempReceptionist);
	delete receptionistInput, tempReceptionist;
}

//Allows the user to delete a staff member.
void RestaurantSystem::deleteStaffMember()
{
	gui::MultiUserInput* deleteStaffInput = new gui::MultiUserInput(affects, "Delete Staff Member!");
	std::string tempFirstName = deleteStaffInput->addFirstNameField("First Name:");
	std::string tempLastName = deleteStaffInput->addLastNameField("Last Name:");

	size_t index = objectSearch(tempFirstName + " " + tempLastName, _staffMembers, &StaffMember::getFullName);

	if (index != -1)
	{
		std::string tempMsg("Staff Member found at index "); tempMsg.insert(tempMsg.size(), std::to_string(index + 1)); tempMsg.push_back('!');
		gui::nextLine(1); gui::printText(tempMsg, *affects._secondaryAffects); gui::nextLine(1); std::this_thread::sleep_for(std::chrono::seconds(2));

		std::swap(_staffMembers[_staffMembers.size() - 1], _staffMembers[index]); _staffMembers.pop_back();

		gui::nextLine(1); gui::printText("Sucessfully deleted staff member!", *affects._secondaryAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	else if (index == -1)
	{
		gui::nextLine(1); gui::printText("STAFF MEMBER NOT FOUND!", *affects._errorAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	delete deleteStaffInput;
}

//Prints all the staff members to the console in a table.
void RestaurantSystem::listStaffMembers()
{
	gui::Table staffTable(affects);

	staffTable.addColumn("Staff Rank", 20, _staffMembers, &StaffMember::getStaffRank);
	staffTable.addColumn("Full Name", 35, _staffMembers, &StaffMember::getFullName);
	staffTable.addColumn("Phone Number", 12, _staffMembers, &StaffMember::getPhoneNumber);
	staffTable.addColumn("Address Line One", 35, _staffMembers, &StaffMember::getAddressLineOne);
	staffTable.addColumn("City", 35, _staffMembers, &StaffMember::getCity);
	staffTable.addColumn("Postcode", 10, _staffMembers, &StaffMember::getPostCode);
	staffTable.addColumn("Time Added", 12, _staffMembers, &StaffMember::getTimeAdded);
	staffTable.addColumn("Date Added", 12, _staffMembers, &StaffMember::getDateAdded);
	staffTable.printTable();

	gui::consolePause(*affects._mainAffects);
}

//Allows the user to add a new customer.
void RestaurantSystem::addCustomer()
{
	gui::MultiUserInput* customerInput = new gui::MultiUserInput(affects, "Add New Customer!");
	Customer* tempCustomer = new Customer(customerInput->addAdressField(), customerInput->addEmailField("Email Address:"), customerInput->addLastNameField("Last Name:"), customerInput->addFirstNameField("First Name:"));
	_customers.push_back(tempCustomer);
	delete customerInput, tempCustomer;
}

//Allows the user to delete a customer.
void RestaurantSystem::deleteCustomer()
{
	gui::MultiUserInput* deleteCustomerInput = new gui::MultiUserInput(affects, "Delete Customer!");
	std::string tempFirstName = deleteCustomerInput->addFirstNameField("First Name:");
	std::string tempLastName = deleteCustomerInput->addLastNameField("Last Name:");

	size_t index = objectSearch(tempFirstName + " " + tempLastName, _customers, &Customer::getFullName);

	if (index != -1)
	{
		std::string tempMsg("Customer found at index "); tempMsg.insert(tempMsg.size(), std::to_string(index + 1)); tempMsg.push_back('!');
		gui::nextLine(1); gui::printText(tempMsg, *affects._secondaryAffects); gui::nextLine(1); std::this_thread::sleep_for(std::chrono::seconds(2));

		std::swap(_customers[_customers.size() - 1], _customers[index]); _customers.pop_back();

		gui::nextLine(1); gui::printText("Sucessfully deleted customer!", *affects._secondaryAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	else if (index == -1)
	{
		gui::nextLine(1); gui::printText("CUSTOMER NOT FOUND!", *affects._errorAffects); gui::nextLine(2); std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	delete deleteCustomerInput;
}

//Prints all the customers to the console in a table.
void RestaurantSystem::listCustomers()
{
	gui::Table customerTable(affects);

	customerTable.addColumn("Full Name", 35, _customers, &Customer::getFullName);
	customerTable.addColumn("Address Line One", 35, _customers, &Customer::getAddressLineOne);
	customerTable.addColumn("City", 35, _customers, &Customer::getCity);
	customerTable.addColumn("Postcode", 10, _customers, &Customer::getPostCode);
	customerTable.addColumn("Email Address", 40, _customers, &Customer::getEmailAddress);
	customerTable.addColumn("Loyal", 7, _customers, &Customer::getStrLoyalCustomer);
	customerTable.addColumn("Orders", 8, _customers, &Customer::getStrAmmountOfOrders);
	customerTable.printTable();

	gui::consolePause(*affects._mainAffects);
}

//Prints a menu for the different cusine types and gets which one the user would like and returns it.
std::string RestaurantSystem::getCuisineType()
{
	gui::Menu cuisineType(affects);
	cuisineType.addTitle("Cuisine Type!"); cuisineType.addDescription("Which cusine type would you like.");

	for (size_t i = 0; i < (sizeof(cuisineTypes) / sizeof(cuisineTypes[0])); i++)
	{
		cuisineType.addChoice(cuisineTypes[i] + "!");
	}
	size_t i = cuisineType.startMenu();
	return cuisineTypes[i];
}

//Universal search function. Which can perform a search for any vector of class objects.
template <typename T, typename R>
size_t RestaurantSystem::objectSearch(const std::string& lookFor, std::vector<T*>& vecOfObjects, R(T::* getter_function_pointer)())
{
	for (size_t i = 0; i < vecOfObjects.size(); i++)
	{
		if (((vecOfObjects[i]->*getter_function_pointer)()) == lookFor)
		{
			return i;
		}
	}
	return -1;
}

//Universal sort function. Which can perform a sort for any vector of class objects.
template <typename T, typename R>
std::vector<T*> RestaurantSystem::objectSort(std::vector<T*> vecOfObjects, R(T::*getter_function_pointer)(), bool accendingOrder)
{
	std::vector<T*> tempVec(vecOfObjects);
	size_t i1, i2;

	for (i1 = 1; i1 < tempVec.size(); i1++)
	{
		std::string tempStr((tempVec[i1]->*getter_function_pointer)());
		i2 = i1 - 1;

		while (i2 >= 0 && (accendingOrder ? ((tempVec[i2]->*getter_function_pointer)()) > tempStr : ((tempVec[i2]->*getter_function_pointer)()) < tempStr))
		{
			std::swap(tempVec[i2 + 1], tempVec[i2]);
			i2 = i2 - 1;
		}
	}
	return tempVec;
}