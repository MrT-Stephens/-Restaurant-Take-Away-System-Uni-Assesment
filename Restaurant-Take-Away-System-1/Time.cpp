#include "Time.h"

Time::Time()
{
	_timeAdded = getTimeString(), _dateAdded = getDateString();
}

Time::Time(const std::string& timeAdded, const std::string& dateAdded) : _timeAdded(timeAdded), _dateAdded(dateAdded) { };

//Returns a formatted string of time (HH:MM:SS).
const std::string Time::getTimeAdded()
{
	return getFormattedTime24(_timeAdded);
}

//Returns a formatted string of date (MM/DD/YYYY).
const std::string Time::getDateAdded()
{
	return getFormattedDate(_dateAdded);
}

//currentDateTime function will get the current date and time and return it using a 'struct tm'.
struct tm Time::currentDateTime()
{
	struct tm currentTime;
	time_t now = time(NULL);
	localtime_s(&currentTime, &now);
	return currentTime;
}

//getFormattedTime24 function returns a string with the time in the correct 24-Hour format (HH:MM:SS).
std::string Time::getFormattedTime24(const std::string& timeString)
{
	std::tm tm;
	char tempTime[10];

	std::istringstream stream(timeString);
	stream >> std::get_time(&tm, "%H:%M:%S");
	std::strftime(tempTime, sizeof(tempTime), "%H:%M:%S", &tm);

	return std::string(tempTime);
}

//getFormattedDate function returns a string with the date in the correct format (DD/MM/YY).
std::string Time::getFormattedDate(const std::string& dateString)
{
	std::tm tm;
	char tempDate[10];

	std::istringstream stream(dateString);
	stream >> std::get_time(&tm, "%m/%d/%Y");
	std::strftime(tempDate, sizeof(tempDate), "%D", &tm);

	return std::string(tempDate);
}

//Gets a string of time (UNFORMATTED).
std::string Time::getTimeString()
{
	std::string timeAdded;
	struct tm currentTime = currentDateTime();

	timeAdded.insert(timeAdded.size(), std::to_string(currentTime.tm_hour));
	timeAdded.insert(timeAdded.size(), ":");
	timeAdded.insert(timeAdded.size(), std::to_string(currentTime.tm_min));
	timeAdded.insert(timeAdded.size(), ":");
	timeAdded.insert(timeAdded.size(), std::to_string(currentTime.tm_sec));

	return timeAdded;
}

//Gets a string of date (UNFORMATTED).
std::string Time::getDateString()
{
	std::string dateAdded;
	struct tm currentTime = currentDateTime();

	dateAdded.insert(dateAdded.size(), std::to_string(currentTime.tm_mon + 1));
	dateAdded.insert(dateAdded.size(), "/");
	dateAdded.insert(dateAdded.size(), std::to_string(currentTime.tm_mday));
	dateAdded.insert(dateAdded.size(), "/");
	dateAdded.insert(dateAdded.size(), std::to_string(currentTime.tm_year + 1900));

	return dateAdded;
}

//Returns a unformatted date string in (MM-DD-YYYY).
std::string Time::getDateStringDash()
{
	std::string dateAdded;
	struct tm currentTime = currentDateTime();

	dateAdded.insert(dateAdded.size(), std::to_string(currentTime.tm_mon + 1));
	dateAdded.insert(dateAdded.size(), "-");
	dateAdded.insert(dateAdded.size(), std::to_string(currentTime.tm_mday));
	dateAdded.insert(dateAdded.size(), "-");
	dateAdded.insert(dateAdded.size(), std::to_string(currentTime.tm_year + 1900));

	return dateAdded;
}