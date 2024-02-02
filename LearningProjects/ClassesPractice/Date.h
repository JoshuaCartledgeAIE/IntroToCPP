#pragma once
class Date
{
	int m_day;
	int m_month;
	int m_year;

public:
	Date();
	Date(int day, int month, int year);
	int SetDate(int day, int month, int year);
	void PrintDate();
};

