#pragma once

#include <iostream>
#include <string>
#include <vector>
#define NOMINMAX    //Wont get the 'MIN' or 'MAX' from 'Windows.h'.
#include <Windows.h>
#include <thread>
#include <chrono>
#include <sstream>

namespace gui
{
	  /***********************************************/
     /*    Console Affects within GUI namespace.    */
    /***********************************************/

    //Escape codes for changing certain aspects of the text in console.
	namespace colour
	{
		const char redForeground[] = "\x1b[31m";
		const char greenForeground[] = "\x1b[32m";
		const char yellowForeground[] = "\x1b[33m";
		const char blueForeground[] = "\x1b[34m";
		const char magentaForeground[] = "\x1b[35m";
		const char cyanForeground[] = "\x1b[36m";
		const char whiteForeground[] = "\x1b[37m";

		const char redBackground[] = "\x1b[41m";
		const char greenBackground[] = "\x1b[42m";
		const char yellowBackground[] = "\x1b[43m";
		const char blueBackground[] = "\x1b[44m";
		const char magentaBackground[] = "\x1b[45m";
		const char cyanBackground[] = "\x1b[46m";
		const char whiteBackground[] = "\x1b[47m";
	}
	namespace affects
	{
		const char bold[] = "\x1b[1m";
		const char italic[] = "\x1b[3m";
		const char underline[] = "\x1b[4m";
		const char blinking[] = "\x1b[5m";
		const char strikethrough[] = "\x1b[9m";
		const char tab[] = "\t";
	}
	const char clearAffects[] = "\x1b[0m";

	  /*******************************************/
     /*    Base class for any GUI component.    */
    /*******************************************/

	class ConsoleAffects
	{
	public:
		std::string* _mainAffects;
		std::string* _secondaryAffects;
		std::string* _errorAffects;
		bool _centreConsole;

		ConsoleAffects(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, bool);
		~ConsoleAffects();
	};

	  /**********************************/
     /*    'Menu' class prototypes.    */
    /**********************************/

	class Menu
	{
	private:
		std::string* _title;
		std::string* _subtitle;
		std::string* _description;
		std::vector<std::string*> _choices;
		unsigned int _mainMenuIndex;
		unsigned int _componentAmmount;

		ConsoleAffects* _affects;
	public:
		Menu(ConsoleAffects&);
		~Menu();

		void addTitle(const std::string&);
		void addSubtitle(const std::string&);
		void addDescription(const std::string&);
		void addChoice(const std::string&);
		unsigned int& startMenu();
	};

	  /*********************************/
     /*    'MultiUserInput' class.    */
    /*********************************/

	class MultiUserInput
	{
	private:
		ConsoleAffects* _affects;
		std::string* _title;
		bool _firstLoop = false;
	public:
		MultiUserInput(ConsoleAffects&, const std::string&);
		~MultiUserInput();

		std::string addFirstNameField(const std::string&);
		std::string addLastNameField(const std::string&);
		std::string addPhoneNumberField(const std::string&);
		std::vector<std::string> addAdressField();
		int addIntegerField(const std::string&);
		long double addMoneyInput(const std::string&, const char&);
		std::string addEmailField(const std::string&);
		std::string addRandomCharWithCapitalField(const std::string&);
		char addYesOrNoField(const std::string&);
		std::vector<unsigned int> addMultiIntegerField(const std::string&, const unsigned int&, const unsigned int&);

		std::string getAddressLineOne();
		std::string getCity();
		std::string getPostCode();

		bool firstNameValidation(const std::string&);
		bool lastNameValidation(const std::string&);
		bool phoneNumberValidation(const std::string&);
		bool addressLineOneValidation(const std::string&);
		bool cityValidation(const std::string&);
		bool postCodeValidation(const std::string&);
		bool integerValidation();
		bool moneyValidation();
		bool emailValidation(const std::string&);
		bool randomCharWithCapitalValidation(const std::string&);
		bool outwardCodeCheck(const std::string&);
		bool inwardCodeCheck(const std::string&);
		bool yesOrNoValidation(const char&);
		bool multiIntegerValidation(const std::string&, const unsigned int&, const unsigned int&);
	};

	  /***********************************/
     /*    'Table' class prototypes.    */
    /***********************************/

	class Table
	{
	private:
		std::vector<std::string*> _columnNames;
		std::vector<unsigned int*> _columnsMaxLength;
		std::vector<std::vector<std::string*>> _tableData;

		ConsoleAffects* _affects;
	public:
		Table(ConsoleAffects&);
		~Table();

		template <typename T, typename R>
		void addColumn(const std::string&, const unsigned int&, std::vector<T*>&, R(T::*)());

		void printTable();
	};

	  /*************************************************/
     /*    Global functions within 'GUI' namespace.   */
    /*************************************************/

	bool capitalAtStart(const std::string&);
	bool allCharacters(const std::string&);
	bool allNumericCharacters(const std::string&);
	bool isAnEmail(const std::string&);
	bool isNumberInside(const std::string&);
	bool isCharInsideButNotAtEnd(const std::string&, const char&);

	std::string formatNum(int, int, char);
	const std::string mergeAffects(const std::vector<std::string>&);
	const std::string addWhitespace(const std::string&, const unsigned int&, bool);
	void printText(const std::string&, const std::string&);
	void nextLine(const short unsigned int&);
	unsigned int getConsoleXval();
	unsigned int getConsoleYval();
	const std::string centreString(const std::string&);
	const std::string insertIntoString(const std::string&, const std::string&, const unsigned int&);
	void consoleCls();
	void consolePause(const std::string&);
	void consoleIgnore(const char&);
	const COORD getConsoleCursor();
	void setConsoleCursor(const COORD&);
	bool isChar(const char&);
	bool isNum(const char&);
}

  /*********************************************/
 /*    'ConsoleAffects' class implemented.    */
/*********************************************/

//ConsoleAffects constuctor and deconstuctor.
gui::ConsoleAffects::ConsoleAffects(const std::vector<std::string>& mainAffects, const std::vector<std::string>& secondaryAffects, const std::vector<std::string>& errorAffects, bool centreConsole) :
	_mainAffects(new std::string(mergeAffects(mainAffects))), _secondaryAffects(new std::string(mergeAffects(secondaryAffects))), _errorAffects(new std::string(mergeAffects(errorAffects))), _centreConsole(centreConsole) { };

gui::ConsoleAffects::~ConsoleAffects() { delete _mainAffects, _secondaryAffects, _errorAffects; };

  /***********************************/
 /*    'Menu' class implemented.    */
/***********************************/

//Menu constuctor and deconstuctor.
gui::Menu::Menu(ConsoleAffects& obj) : _affects(&obj) { };

gui::Menu::~Menu()
{
	delete _title, _subtitle, _description, _affects;

	for (size_t i = 0; i < _choices.size(); i++)
	{
		delete (_choices[i]);
	}
	_choices.clear();
}

//addTilte function. Allows you to add a title to the menu.
void gui::Menu::addTitle(const std::string& message)
{
	_title = new std::string(message);
	_componentAmmount += 2;
}

//addSubtitle function. Allows you to add a subtitle to the menu.
void gui::Menu::addSubtitle(const std::string& message)
{
	_subtitle = new std::string(message);
	_componentAmmount += 2;
}

//addDescription function. Allows you to add a description to the menu.
void gui::Menu::addDescription(const std::string& message)
{
	_description = new std::string(message);
	_componentAmmount += 2;
}

//addChoice function. Allows you to add a choices to the menu.
void gui::Menu::addChoice(const std::string& message)
{
	_choices.push_back(new std::string(message));
	_componentAmmount++;
}

//startMenu function. Prints the menu and returns the number that the user enters.
unsigned int& gui::Menu::startMenu()
{
	bool correct = false; consoleCls();
	do
	{
		std::string str("Please enter a number between 0 and "), errorMsg("INVALID NUMBER ENTERED!");
		unsigned int consoleXvalue = getConsoleXval(), consoleYvalue = getConsoleYval();    //Gets the 'x' and 'y' sizes of the console.

		if (_affects->_centreConsole)
		{
			COORD coord = { 0, ceil((consoleYvalue - (_componentAmmount + 4)) / 2) };
			setConsoleCursor(coord);    //Sets the console cursor location to accomidate for the centring of the console.
		}
		if (_title != NULL)    //Checks for a NULL pointer.
		{
			std::string* tempTitle = new std::string(addWhitespace(*_title, ceil((consoleXvalue - (_title->size())) / 2), false));
			std::cout << *_affects->_mainAffects << gui::affects::bold << ((_affects->_centreConsole) ? insertIntoString(*tempTitle, gui::affects::underline, (tempTitle->size() - _title->size())) : gui::affects::underline + *_title) << gui::clearAffects << "\n\n";
			delete tempTitle;
		}
		if (_subtitle != NULL)    //Checks for a NULL pointer.
		{
			std::cout << *_affects->_secondaryAffects << gui::affects::bold << ((_affects->_centreConsole) ? addWhitespace(*_subtitle, ceil((consoleXvalue - (_subtitle->size())) / 2), false) : *_subtitle) << gui::clearAffects << "\n\n";
		}
		if (_description != NULL)    //Checks for a NULL pointer.
		{
			std::cout << *_affects->_secondaryAffects << gui::affects::italic << ((_affects->_centreConsole) ? addWhitespace(*_description, ceil((consoleXvalue - (_description->size())) / 2), false) : *_description) << gui::clearAffects << "\n\n";
		}

		double midPointAverage = 0;
		if (_affects->_centreConsole)
		{
			for (size_t i = 0; i < _choices.size(); i++)    //Works out the ammount of whitespace that needs to be added to each choice to centre it in the console.
			{
				midPointAverage += (_choices[i]->size() + 6);
			}
			midPointAverage = midPointAverage / static_cast<double>(_choices.size());
		}

		for (size_t i = 0; i < _choices.size(); i++)    //Prints all the choices to the console.
		{
			std::cout << *_affects->_mainAffects << ((_affects->_centreConsole) ? addWhitespace("(" + std::to_string(i) + ")", ceil((consoleXvalue - midPointAverage) / 2), false) : "(" + std::to_string(i) + ")")
				<< " - " << gui::clearAffects << *_affects->_secondaryAffects << *_choices[i] << "\n";
		}

		//Gets the users input.
		std::cout << "\n";
		std::cout << *_affects->_mainAffects << ((_affects->_centreConsole) ? addWhitespace(str, ceil((consoleXvalue - (str.size() + 4)) / 2), false) : str) << _choices.size() - 1 << ": " << gui::clearAffects << *_affects->_secondaryAffects;
		std::cin >> _mainMenuIndex;
		std::cout << gui::clearAffects;

		if (!std::cin.fail() && _mainMenuIndex >= 0 && _mainMenuIndex <= _choices.size() - 1)    //Validates the users input and checks if its correct.
		{
			correct = true;
			consoleCls();
		}
		else if (!correct)    //If the users input was not correct.
		{
			correct = false;
			std::string* tempError = new std::string(addWhitespace(errorMsg, ceil((consoleXvalue - (errorMsg.size())) / 2), false));
			std::cerr << ((_affects->_centreConsole) ? insertIntoString(*tempError, *_affects->_errorAffects, (tempError->size() - errorMsg.size())) : *_affects->_errorAffects + errorMsg) << gui::clearAffects;
			delete tempError;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::this_thread::sleep_for(std::chrono::seconds(1));
			consoleCls();
		}
	} while (!correct);

	return _mainMenuIndex;    //Returns the users entered number.
}

  /*********************************************/
 /*    'MultiUserInput' class implemented.    */
/*********************************************/

//MultiUserInput constuctors and deconstuctors.
gui::MultiUserInput::MultiUserInput(ConsoleAffects& obj, const std::string& title) : _affects(&obj), _title(new std::string(title))
{
	std::cout << *_affects->_mainAffects << title << gui::clearAffects << "\n";
};

gui::MultiUserInput::~MultiUserInput() { delete _title; };

//addFirstNameField function. Which gets a first name from the user and calls a function to validate it. If correct will return it.
std::string gui::MultiUserInput::addFirstNameField(const std::string& fieldName)
{
	std::string inputVariable;
	std::cout << *_affects->_mainAffects << "\n" << fieldName << gui::clearAffects << *_affects->_secondaryAffects << "\t";
	std::cin >> inputVariable; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cout << gui::clearAffects;

	return (firstNameValidation(inputVariable) ? inputVariable : addFirstNameField(fieldName));    //Recursive function, if the user input was not correct.
}

//addLastNameField function. Which gets a last name from the user and calls a function to validate it. If correct will return it.
std::string gui::MultiUserInput::addLastNameField(const std::string& fieldName)
{
	std::string inputVariable;
	std::cout << *_affects->_mainAffects << "\n" << fieldName << gui::clearAffects << *_affects->_secondaryAffects << "\t";
	std::cin >> inputVariable; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cout << gui::clearAffects;

	return (lastNameValidation(inputVariable) ? inputVariable : addLastNameField(fieldName));    //Recursive function, if the user input was not correct.
}

//addPhoneNumberField function. Which gets a phone number from the user and calls a function to validate it. If correct will return it.
std::string gui::MultiUserInput::addPhoneNumberField(const std::string& fieldName)
{
	std::string inputVariable;
	std::cout << *_affects->_mainAffects << "\n" << fieldName << gui::clearAffects << *_affects->_secondaryAffects << "\t";
	std::cin >> inputVariable; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cout << gui::clearAffects;

	return (phoneNumberValidation(inputVariable) ? inputVariable : addPhoneNumberField(fieldName));    //Recursive function, if the user input was not correct.
}

//addAdressField function. Which calls function to get each part of the address and this will put those parts into a vector and return it.
std::vector<std::string> gui::MultiUserInput::addAdressField()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::vector<std::string> address;
	address.push_back(getAddressLineOne());
	address.push_back(getCity());
	address.push_back(getPostCode());

	return address;
}

//getAddressLineOne function. Which gets a address line one from the user and calls a function to validate it. If correct will return it.
std::string gui::MultiUserInput::getAddressLineOne()
{
	std::string inputVariable;
	std::cout << *_affects->_mainAffects << "\nEnter Address Line One:" << gui::clearAffects << *_affects->_secondaryAffects << "\t";
	std::getline(std::cin, inputVariable); std::cout << gui::clearAffects;

	return (addressLineOneValidation(inputVariable) ? inputVariable : getAddressLineOne());    //Recursive function, if the user input was not correct.
}

//getPostCode function. Which gets a postcode from the user and calls a function to validate it. If correct will return it.
std::string gui::MultiUserInput::getPostCode()
{
	std::string inputVariable;
	std::cout << *_affects->_mainAffects << "\nEnter Postcode:" << gui::clearAffects << *_affects->_secondaryAffects << "\t";
	std::getline(std::cin, inputVariable); std::cout << gui::clearAffects;

	return (postCodeValidation(inputVariable) ? inputVariable : getPostCode());    //Recursive function, if the user input was not correct.
}

//getCity function. Which gets a city from the user and calls a function to validate it. If correct will return it.
std::string gui::MultiUserInput::getCity()
{
	std::string inputVariable;
	std::cout << *_affects->_mainAffects << "\nEnter City:" << gui::clearAffects << *_affects->_secondaryAffects << "\t";
	std::getline(std::cin, inputVariable); std::cout << gui::clearAffects;

	return (cityValidation(inputVariable) ? inputVariable : getCity());    //Recursive function, if the user input was not correct.
}

//addIntegerField function. Which gets a integer from the user and calls a function to validate it. If correct will return it.
int gui::MultiUserInput::addIntegerField(const std::string& fieldName)
{
	int inputVariable;
	std::cout << *_affects->_mainAffects << "\n" << fieldName << gui::clearAffects << *_affects->_secondaryAffects << "\t";
	std::cin >> inputVariable; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cout << gui::clearAffects;

	return (integerValidation() ? inputVariable : addIntegerField(fieldName));    //Recursive function, if the user input was not correct.
}

//addMoneyInput function. Which gets a floating point number from the user and calls a function to validate it. If correct will return it.
long double gui::MultiUserInput::addMoneyInput(const std::string& fieldName, const char& moneySymbol)
{
	long double inputVariable;
	std::cout << *_affects->_mainAffects << "\n" << fieldName << gui::clearAffects << *_affects->_secondaryAffects << "\t" << moneySymbol << " ";
	std::cin >> inputVariable; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cout << gui::clearAffects;

	return (moneyValidation() ? inputVariable : addMoneyInput(fieldName, moneySymbol));    //Recursive function, if the user input was not correct.
}

//addEmailField function. Which gets a email address from the user and calls a function to validate it. If correct will return it.
std::string gui::MultiUserInput::addEmailField(const std::string& fieldName)
{
	std::string inputVariable;
	std::cout << *_affects->_mainAffects << "\n" << fieldName << gui::clearAffects << *_affects->_secondaryAffects << "\t";
	std::cin >> inputVariable; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cout << gui::clearAffects;

	return (emailValidation(inputVariable) ? inputVariable : addEmailField(fieldName));    //Recursive function, if the user input was not correct.
}

//addRandomCharWithCapitalField function. Which gets a email address from the user and calls a function to validate it. If correct will return it.
std::string gui::MultiUserInput::addRandomCharWithCapitalField(const std::string& fieldName)
{
	std::string inputVariable;
	std::cout << *_affects->_mainAffects << "\n" << fieldName << gui::clearAffects << *_affects->_secondaryAffects << "\t";
	if (!_firstLoop) { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); _firstLoop = true; };
	std::getline(std::cin, inputVariable); std::cout << gui::clearAffects;

	return (randomCharWithCapitalValidation(inputVariable) ? inputVariable : addRandomCharWithCapitalField(fieldName));    //Recursive function, if the user input was not correct.
}

//addYesOrNoField function. Which gets a 'y' or 'n' from the user and calls a function to validate it. If correct will return it.
char gui::MultiUserInput::addYesOrNoField(const std::string& fieldName)
{
	char inputVariable;
	std::cout << *_affects->_mainAffects << "\n" << fieldName << gui::clearAffects << *_affects->_secondaryAffects << "\t";
	std::cin >> inputVariable; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cout << gui::clearAffects;

	return (yesOrNoValidation(inputVariable) ? inputVariable : addYesOrNoField(fieldName));    //Recursive function, if the user input was not correct.
}

//addMultiIntegerField function. Which gets multiple integers from the user and calls a function to validate it. If correct will return it.
std::vector<unsigned int> gui::MultiUserInput::addMultiIntegerField(const std::string& fieldName, const unsigned int& startingRange, const unsigned int& endingRange)
{
	std::string inputVariable, temp; std::vector<unsigned int> numbers;
	std::cout << *_affects->_mainAffects << "\n" << fieldName << gui::clearAffects << *_affects->_secondaryAffects << "\t";
	std::getline(std::cin, inputVariable); std::cout << gui::clearAffects;

	if (multiIntegerValidation(inputVariable, startingRange, endingRange))
	{
		std::stringstream ss(inputVariable);
		try {
			while (ss >> temp) { numbers.push_back(std::stoi(temp)); }   //Splits up all the induvidual integers.
		}
		catch (const std::exception& ex)
		{
			std::cerr << *_affects->_errorAffects << "ENTER VALID NUMBERS!" << gui::clearAffects << "\n";
		}

		return numbers;
	}
	else
	{
		return addMultiIntegerField(fieldName, startingRange, endingRange);     //Recursive function, if the user input was not correct.
	}
}

//first name validation function.
bool gui::MultiUserInput::firstNameValidation(const std::string& str)
{
	if (!capitalAtStart(str))
	{
		std::cerr << *_affects->_errorAffects << "NEED CAPITAL AT THE BEGINING!" << gui::clearAffects << "\n";
		return false;
	}
	if (!allCharacters(str))
	{
		std::cerr << *_affects->_errorAffects << "MUST BE ONLY ALPHABETIC CHARACTERS!" << gui::clearAffects << "\n";
		return false;
	}
	if (str.size() <= 2)
	{
		std::cerr << *_affects->_errorAffects << "MUST BE MORE THAN 2 CHARACTERS LONG!" << gui::clearAffects << "\n";
		return false;
	}
	return true;
}

//last name validation function.
bool gui::MultiUserInput::lastNameValidation(const std::string& str)
{
	if (!capitalAtStart(str))
	{
		std::cerr << *_affects->_errorAffects << "NEED CAPITAL AT THE BEGINING!" << gui::clearAffects << "\n";
		return false;
	}
	if (!allCharacters(str))
	{
		std::cerr << *_affects->_errorAffects << "MUST BE ONLY ALPHABETIC CHARACTERS!" << gui::clearAffects << "\n";
		return false;
	}
	if (str.size() <= 2)
	{
		std::cerr << *_affects->_errorAffects << "MUST BE MORE THAN 2 CHARACTERS LONG!" << gui::clearAffects << "\n";
		return false;
	}
	return true;
}

//phone number validation function.
bool gui::MultiUserInput::phoneNumberValidation(const std::string& str)
{
	if (!allNumericCharacters(str))
	{
		std::cerr << *_affects->_errorAffects << "MUST BE ONLY NUMERIC CHARACTERS!" << gui::clearAffects << "\n";
		return false;
	}
	if (str.size() <= 6)
	{
		std::cerr << *_affects->_errorAffects << "MUST BE MORE THAN 6 CHARACTERS LONG!" << gui::clearAffects << "\n";
		return false;
	}
	return true;
}

//address line one validation function.
bool gui::MultiUserInput::addressLineOneValidation(const std::string& str)
{
	std::stringstream ss(str); std::string word; std::vector<std::string> words;
	while (ss >> word) { words.push_back(word); }    //Spits the string up into induvidual words.

	if (words.size() == 0)
	{
		std::cerr << *_affects->_errorAffects << "CANNOT BE EMPTY!" << gui::clearAffects << "\n";
		return false;
	}
	else if (words.size() == 1)
	{
		if (words[0].size() <= 2)
		{
			std::cerr << *_affects->_errorAffects << "MUST BE MORE THAN 2 CHARACTERS LONG!" << gui::clearAffects << "\n";
			return false;
		}
		if (!allCharacters(words[0]))
		{
			std::cerr << *_affects->_errorAffects << "MUST BE STREET ADDRESS OR HOUSE NAME!" << gui::clearAffects << "\n";
			return false;
		}
		if (!capitalAtStart(words[0]))
		{
			std::cerr << *_affects->_errorAffects << "MUST BE A CAPITAL LETTER AT THE START!" << gui::clearAffects << "\n";
			return false;
		}
	}
	else if (words.size() > 1)
	{
		if (allNumericCharacters(words[0]))
		{
			for (size_t i = 1; i < words.size(); i++)
			{
				if (words[i].size() <= 2)
				{
					std::cerr << *_affects->_errorAffects << "MUST BE MORE THAN 2 CHARACTERS LONG!" << gui::clearAffects << "\n";
					return false;
				}
				if (!allCharacters(words[i]))
				{
					std::cerr << *_affects->_errorAffects << "MUST HOUSE NUMBER FOLLOWED BY STREET NAME!" << gui::clearAffects << "\n";
					return false;
				}
				if (!capitalAtStart(words[i]))
				{
					std::cerr << *_affects->_errorAffects << "MUST BE A CAPITAL LETTER AT THE START!" << gui::clearAffects << "\n";
					return false;
				}
			}
		}
		else if (allCharacters(words[0]))
		{
			for (size_t i = 0; i < words.size(); i++)
			{
				if (words[i].size() <= 2)
				{
					std::cerr << *_affects->_errorAffects << "MUST BE MORE THAN 2 CHARACTERS LONG!" << gui::clearAffects << "\n";
					return false;
				}
				if (!allCharacters(words[i]))
				{
					std::cerr << *_affects->_errorAffects << "MUST HOUSE NAME FOLLOWED BY STREET NAME!" << gui::clearAffects << "\n";
					return false;
				}
				if (!capitalAtStart(words[i]))
				{
					std::cerr << *_affects->_errorAffects << "MUST BE A CAPITAL LETTER AT THE START!" << gui::clearAffects << "\n";
					return false;
				}
			}
		}
		else if (!allNumericCharacters(words[0]) || allCharacters(words[0]))
		{
			std::cerr << *_affects->_errorAffects << "MUST BE A VALID CHARACTER SEQUENCE!" << gui::clearAffects << "\n";
			return false;
		}
	}
	return true;
}

//city validation function.
bool gui::MultiUserInput::cityValidation(const std::string& str)
{
	std::stringstream ss(str); std::string word; std::vector<std::string> words;
	while (ss >> word) { words.push_back(word); }

	for (size_t i = 0; i < words.size(); i++)
	{
		if (!capitalAtStart(words[i]))
		{
			std::cerr << *_affects->_errorAffects << "NEED CAPITAL AT THE BEGINING!" << gui::clearAffects << "\n";
			return false;
		}
		if (!allCharacters(words[i]))
		{
			std::cerr << *_affects->_errorAffects << "MUST BE ONLY ALPHABETIC CHARACTERS!" << gui::clearAffects << "\n";
			return false;
		}
		if (words[i].size() <= 2)
		{
			std::cerr << *_affects->_errorAffects << "MUST BE MORE THAN 2 CHARACTERS LONG!" << gui::clearAffects << "\n";
			return false;
		}
	}
	return true;
}

//post code validation function. Checks for all posabilites of a postcode.
bool gui::MultiUserInput::postCodeValidation(const std::string& str)
{
	//Postcode key patterns: https://ideal-postcodes.co.uk/guides/uk-postcode-format!
	if (str.empty())
	{
		std::cerr << *_affects->_errorAffects << "CANNOT BE EMPTY!" << gui::clearAffects << "\n";
		return false;
	}
	else if (str.find(' ') != std::string::npos)
	{
		if (str.size() < 6 || str.size() > 8)
		{
			std::cerr << *_affects->_errorAffects << "MUST BE 6 - 8 CHARACTERS LONG!" << gui::clearAffects << "\n";
			return false;
		}
		std::string::size_type position = str.find(' ');
		std::string outwardCode = str.substr(0, position);
		std::string inwardCode = str.substr(position + 1);

		if (!outwardCodeCheck(outwardCode))
		{
			std::cerr << *_affects->_errorAffects << "INCORRECT OUTWARD CODE FORMAT!" << gui::clearAffects << "\n";
			return false;
		}
		if (!inwardCodeCheck(inwardCode))
		{
			std::cerr << *_affects->_errorAffects << "INCORRECT INWARD CODE FORMAT!" << gui::clearAffects << "\n";
			return false;
		}
	}
	else if (!(str.find(' ') != std::string::npos))
	{
		if (str.size() < 5 || str.size() > 7)
		{
			std::cerr << *_affects->_errorAffects << "MUST BE 5 - 7 CHARACTERS LONG!" << gui::clearAffects << "\n";
			return false;
		}
		std::string outwardCode = str.substr(0, str.size() - 3);
		std::string inwardCode = str.substr(str.size() - 3);

		if (!outwardCodeCheck(outwardCode))
		{
			std::cerr << *_affects->_errorAffects << "INCORRECT OUTWARD CODE FORMAT!" << gui::clearAffects << "\n";
			return false;
		}
		if (!inwardCodeCheck(inwardCode))
		{
			std::cerr << *_affects->_errorAffects << "INCORRECT INWARD CODE FORMAT!" << gui::clearAffects << "\n";
			return false;
		}
	}
	return true;
}

//post code outward code check.
bool gui::MultiUserInput::outwardCodeCheck(const std::string& str)
{
	if (str.size() == 2 && isChar(str[0]) && isNum(str[1]))
	{
		return true;
	}
	else if (str.size() == 3)
	{
		if (isChar(str[0]) && isNum(str[1]))
		{
			if (isChar(str[2]))
			{
				return true;
			}
			else if (isNum(str[2]))
			{
				return true;
			}
		}
		else if (isChar(str[0]) && isChar(str[1]) && isNum(str[2]))
		{
			return true;
		}
	}
	else if (str.size() == 4)
	{
		if (isChar(str[0]) && isChar(str[1]) && isNum(str[2]))
		{
			if (isChar(str[3]))
			{
				return true;
			}
			else if (isNum(str[3]))
			{
				return true;
			}
		}
	}
	return false;
}

//post code inward code check.
bool gui::MultiUserInput::inwardCodeCheck(const std::string& str)
{
	if (str.size() == 3)
	{
		if (isNum(str[0]) && isChar(str[1]) && isChar(str[2]))
		{
			return true;
		}
	}
	return false;
}

//integer validation function.
bool gui::MultiUserInput::integerValidation()
{
	if (std::cin.fail())
	{
		std::cin.clear(); std::cin.ignore(1000, '\n');
		std::cerr << *_affects->_errorAffects << "MUST BE ONLY NUMERIC CHARACTERS!" << gui::clearAffects << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return false;
	}
	return true;
}

//money input validation function.
bool gui::MultiUserInput::moneyValidation()
{
	if (std::cin.fail())
	{
		std::cin.clear(); std::cin.ignore(1000, '\n');
		std::cerr << *_affects->_errorAffects << "MUST BE ONLY NUMERIC CHARACTERS!" << gui::clearAffects << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return false;
	}
	return true;
}

//email validaition function.
bool gui::MultiUserInput::emailValidation(const std::string& str)
{
	const std::string invalidChars = "!#$%^&*()=+[]~¬`{}\\|;:\"' ,<>/?";

	std::string::size_type position = str.find('@');
	std::string::size_type dotPosition = str.find('.');
	std::string firstPart = str.substr(0, position);
	std::string secondPart = str.substr(position + 1);

	if (firstPart.size() <= 3 || secondPart.size() <= 3)
	{
		std::cerr << *_affects->_errorAffects << "MUST BE LONGER THAN 7 CHARACTERS!" << gui::clearAffects << "\n";
		return false;
	}
	if (!(str.find('@') != std::string::npos))
	{
		std::cerr << *_affects->_errorAffects << "MUST HAVE ONE '@'!" << gui::clearAffects << "\n";
		return false;
	}
	if (!(secondPart.find('.') != std::string::npos) || (dotPosition == str.size() - 1))
	{
		std::cerr << *_affects->_errorAffects << "MUST HAVE ONE '.' AFTER '@' (NOT AT END)!" << gui::clearAffects << "\n";
		return false;
	}
	if (str.find_first_of(invalidChars) != std::string::npos)
	{
		std::cerr << *_affects->_errorAffects << "CANT HAVE OTHER SYMBOLS THAN '@.-_'!" << gui::clearAffects << "\n";
		return false;
	}
	return true;
}

//randow string input validation.
bool gui::MultiUserInput::randomCharWithCapitalValidation(const std::string& str)
{
	std::stringstream ss(str); std::string word; std::vector<std::string> words;
	while (ss >> word) { words.push_back(word); }

	if (str.empty())
	{
		std::cerr << *_affects->_errorAffects << "CANNOT BE EMPTY!" << gui::clearAffects << "\n";
		return false;
	}

	for (size_t i = 0; i < words.size(); i++)
	{
		if (!capitalAtStart(words[i]))
		{
			std::cerr << *_affects->_errorAffects << "NEED CAPITAL AT THE BEGINING!" << gui::clearAffects << "\n";
			return false;
		}
		if (!allCharacters(words[i]))
		{
			std::cerr << *_affects->_errorAffects << "MUST BE ONLY ALPHABETIC CHARACTERS!" << gui::clearAffects << "\n";
			return false;
		}
		if (words[i].size() <= 2)
		{
			std::cerr << *_affects->_errorAffects << "MUST BE MORE THAN 2 CHARACTERS LONG!" << gui::clearAffects << "\n";
			return false;
		}
	}
	return true;
}

//'y' or 'n' validation function.
bool gui::MultiUserInput::yesOrNoValidation(const char& c)
{
	if (std::toupper(c) != 'Y' && std::toupper(c) != 'N')
	{
		std::cerr << *_affects->_errorAffects << "ENTER 'Y' OR 'N' TO CONTINUE!" << gui::clearAffects << "\n";
		return false;
	}
	return true;
}

//multi-integer validation function.
bool gui::MultiUserInput::multiIntegerValidation(const std::string& numbers, const unsigned int& startingRange, const unsigned int& endingRange)
{
	std::stringstream ss(numbers); std::vector<std::string> strNumbers; std::string temp;
	while (ss >> temp) { strNumbers.push_back(temp); }

	for (size_t i = 0; i < strNumbers.size(); i++)
	{
		if (!allNumericCharacters(strNumbers[i]))
		{
			std::cerr << *_affects->_errorAffects << "MUST BE ONLY NUMERIC CHARACTERS!" << gui::clearAffects << "\n";
			return false;
		}
		if (allNumericCharacters(strNumbers[i]))
		{
			if (std::stoi(strNumbers[i]) < startingRange)
			{
				std::cerr << *_affects->_errorAffects << "MUST BE GREATER THAN " << startingRange << "!" << gui::clearAffects << "\n";
				return false;
			}
			if (std::stoi(strNumbers[i]) > endingRange)
			{
				std::cerr << *_affects->_errorAffects << "MUST BE LESS THAN " << endingRange << "!" << gui::clearAffects << "\n";
				return false;
			}
		}
	}
	return true;
}

  /************************************/
 /*    'Table' class implemented.    */
/************************************/

//Table constuctor and deconstuctor.
gui::Table::Table(ConsoleAffects& obj) : _affects(&obj) { };

gui::Table::~Table()
{
	for (size_t i = 0; i < _columnNames.size(); i++)
	{
		delete (_columnNames[i]);
	}
	_columnNames.clear();

	for (size_t i = 0; i < _columnsMaxLength.size(); i++)
	{
		delete (_columnsMaxLength[i]);
	}
	_columnsMaxLength.clear();

	for (size_t i0 = 0; i0 < _tableData.size(); i0++)
	{
		for (size_t i1 = 0; i1 < _tableData[i0].size(); i1++)
		{
			delete (_tableData[i0][i1]);
		}
		_tableData[i0].clear();
	}
	_tableData.clear();
}

//addColumn function. Allows you to add a column to the table that will get printed.
template <typename T, typename R>
void gui::Table::addColumn(const std::string& columnName, const unsigned int& maxCharSize, std::vector<T*>& obj, R(T::* memberFunc)())
{
	_columnNames.push_back(new std::string(columnName));
	_columnsMaxLength.push_back(new unsigned int(maxCharSize));

	std::vector<std::string*> column;
	for (size_t i = 0; i < obj.size(); i++)
	{
		auto result = (obj[i]->*memberFunc)();    //Gets the objects data using the passed in pointer to the objects function.
		column.push_back(new std::string(result));    //Appends the data to the back of a tempuary vector.
	}
	_tableData.push_back(column);    //Apeends the tempuary vector to the back of the '_tableData' vector.
}

//printTable function. Will print the table function to the console.
void gui::Table::printTable()
{
	std::cout << *_affects->_mainAffects << " Num | ";
	for (size_t i = 0; i < _columnNames.size(); i++)
	{
		std::cout << *_affects->_mainAffects << gui::addWhitespace(*_columnNames[i], *_columnsMaxLength[i], true) << gui::clearAffects << *_affects->_mainAffects << " | ";
	}
	std::cout << gui::clearAffects << "\n";

	for (size_t i1 = 0; i1 < _tableData[0].size(); i1++)
	{
		std::cout << *_affects->_secondaryAffects << gui::formatNum(i1 + 1, 4, ' ') << gui::clearAffects << *_affects->_mainAffects << " | " << gui::clearAffects;

		for (size_t i0 = 0; i0 < _tableData.size(); i0++)
		{
			std::cout << gui::clearAffects << *_affects->_secondaryAffects << gui::addWhitespace(*_tableData[i0][i1], *_columnsMaxLength[i0], true) << gui::clearAffects << *_affects->_mainAffects << " | ";
		}
		std::cout << gui::clearAffects << "\n";
	}
	std::cout << "\n";
}

  /******************************************************/
 /*    Global functions within the 'gui' namespace.    */
/******************************************************/

//mergeAffects function. Takes in a vector of strings and merges those strings into one long string.
const std::string gui::mergeAffects(const std::vector<std::string>& affects)
{
	std::string temp;
	for (const auto i : affects)
	{
		temp.insert(temp.size(), i);
	}
	return temp;
}

//getConsoleXval function. Gets the size of the consoles x axis.
unsigned int gui::getConsoleXval()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(console, &info);
	return info.dwSize.X;
}

//getConsoleYval function. Gets the size of the consoles y axis.
unsigned int gui::getConsoleYval()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(console, &info);
	return info.dwSize.Y;
}

//getConsoleCursor function. Gets the consoles cursor position and returns as a COORD variable.
const COORD gui::getConsoleCursor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD currentPosition = csbi.dwCursorPosition;
	return currentPosition;
}

//setConsoleCursor function. Sets the location of the consoles cursor position.
void gui::setConsoleCursor(const COORD& location)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, location);
}

//formatNum function returns a string of a formatted passed in mumber. Will insert a passed in digit in the front of the number to a desired passed in length.
std::string gui::formatNum(int num, int length, char insertChar) {
	std::string temp(std::to_string(num));
	std::string str(1, insertChar);

	for (size_t i = 0; i < length; i++)
	{
		temp = temp.size() != length ? temp.insert(0, str) : temp;
	}
	return temp;
}

//addWhitespace function. Adds whitespace to either the front or the back of a string.
const std::string gui::addWhitespace(const std::string& str, const unsigned int& numOfBlank, bool backOfString)
{
	std::string temp(str);
	for (size_t i = ((backOfString) ? temp.size() : 0); i < numOfBlank; i++)
	{
		temp.insert(((backOfString) ? i : 0), " ");
	}
	return temp;
}

//centreString function. Centres a passed in string in the consoles x axis.
const std::string gui::centreString(const std::string& str)
{
	std::string temp(str);
	return addWhitespace(str, ceil((getConsoleXval() - str.size()) / 2), false);
}

//insertIntoString function. Inserts a passed in string into another sting at a desired location.
const std::string gui::insertIntoString(const std::string& str, const std::string& insertStr, const unsigned int& location)
{
	std::string temp(str);
	return temp.insert(location, insertStr);
}

//printText function. Prints text to the console using the ConsoleAddects object.
void gui::printText(const std::string& text, const std::string& affects)
{
	std::cout << affects << text << gui::clearAffects;
}

//Simple function that prints the end line character into the console for a desired ammount.
void gui::nextLine(const short unsigned int& ammount)
{
	for (short unsigned int i = 0; i < ammount; i++)
	{
		std::cout << "\n";
	}
}

//Clears everything within the console.
void gui::consoleCls() { system("cls"); };

//Pauses the console, until any key is pressed.
void gui::consolePause(const std::string& affect) { std::cout << affect, system("pause"), std::cout << gui::clearAffects; };

//Ignroes everying in the cin stream up to a desired character. 
void gui::consoleIgnore(const char& c) { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), c); };

//Checks for a capital letter at the start of a string.
bool gui::capitalAtStart(const std::string& str)
{
	const char characters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	for (size_t i = 0; i < 26; i++)
	{
		if (str[0] == characters[i])
		{
			return true;
		}
	}
	return false;
}

//Makes sure a string is all characters.
bool gui::allCharacters(const std::string& str)
{
	unsigned int count = 0;
	const char characters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	for (size_t i0 = 0; i0 < str.size(); i0++)
	{
		for (size_t i1 = 0; i1 < 26; i1++)
		{
			if (std::toupper(str[i0]) == characters[i1])
			{
				count++;
			}
		}
	}
	return (count == str.size()) ? true : false;
}

//Makes sure a singe character is a character.
bool gui::isChar(const char& c)
{
	const char characters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	for (size_t i = 0; i < 26; i++)
	{
		if (std::toupper(c) == characters[i])
		{
			return true;
		}
	}
	return false;
}

//Makes sure a characters is a numerical digit.
bool gui::isNum(const char& c)
{
	const char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	for (size_t i = 0; i < 10; i++)
	{
		if (c == numbers[i])
		{
			return true;
		}
	}
	return false;
}

//Checks a string to make sure its all numerical values.
bool gui::allNumericCharacters(const std::string& str)
{
	unsigned int count = 0;
	const char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	for (size_t i0 = 0; i0 < str.size(); i0++)
	{
		for (size_t i1 = 0; i1 < 10; i1++)
		{
			if (str[i0] == numbers[i1])
			{
				count++;
			}
		}
	}
	return (count == str.size()) ? true : false;
}

//Checks for a numerical character within a string.
bool gui::isNumberInside(const std::string& str)
{
	const char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	for (size_t i0 = 0; i0 < str.size(); i0++)
	{
		for (size_t i1 = 0; i1 < 10; i1++)
		{
			if (str[i0] == numbers[i1])
			{
				return true;
			}
		}
	}
	return false;
}

//Checks for a desired character within a string but not at the end of the string.
bool gui::isCharInsideButNotAtEnd(const std::string& str, const char& character)
{
	for (size_t i = 0; i < str.size() - 1; i++)
	{
		if (str[i] == character)
		{
			return true;
		}
	}
	return false;
}