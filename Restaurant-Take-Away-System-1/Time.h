#pragma once

#include <time.h>
#include <string>
#include <sstream>
#include <iomanip>

  /***********************/
 /*    'Time' class.    */
/***********************/

class Time {
protected:
	std::string _timeAdded;
	std::string _dateAdded;
public:
	Time();
	Time(const std::string&, const std::string&);
	const std::string getTimeAdded();
	const std::string getDateAdded();
	struct tm currentDateTime();
	std::string getFormattedTime24(const std::string& timeString);
	std::string getFormattedDate(const std::string& dateString);
	std::string getTimeString();
	std::string getDateString();
	std::string getDateStringDash();
};