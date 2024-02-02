#include "Date.h"
#include <iostream>


int Date::SetDate(int day, int month, int year)
{
	const int DAYS_PER_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month <= 1 || month >= 12) { // check month first so that the index is okay before checking the days per month array
		std::cout << day << "/" << month << "/" << year << " is an invalid date!" << std::endl;
		return 1;
		
	}else if ((day <= 1 || day >= DAYS_PER_MONTH[month - 1]) || (year < 0)) {
		std::cout << day << "/" << month << "/" << year << " is an invalid date!" << std::endl;
		return 1;
	}
	

	m_day = day;
	m_month = month;
	m_year = year;
	return 0;
}

void Date::PrintDate() {
	std::cout << m_day << "/" << m_month << "/" << m_year << std::endl;
}

Date::Date(int day, int month, int year)
{
	if (SetDate(day, month, year) == 1) {
		SetDate(1, 1, 2000);
	}
}

Date::Date()
{
	SetDate(1, 1, 2000);
}
