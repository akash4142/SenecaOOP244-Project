/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>
#include "Utils.h"
#include "Date.h"

using namespace std;

namespace sdds
{ 
	
	Date::Date()
	{
		dateOnlyValue = false;
		getSystemDate(this->m_year, this->m_month, this->m_day, this->hour, this->minute, dateOnlyValue);
	}


	Date::Date(int m_year, int m_month, int m_day, int hour, int minute)
	{
		if (hour == 0 && minute == 0) dateOnlyValue = true;
		else dateOnlyValue = false;

		setDate(m_year, m_month, m_day, hour, minute);
		validateDate(m_year, m_month, m_day, hour, minute);
	}


	void Date::setDate(const int m_year, const int m_month, const int m_day, const int hour, const int minute)
	{
		this->m_year = m_year;
		this->m_month = m_month;
		this->m_day = m_day;
		this->hour = hour;
		this->minute = minute;
	}


	void Date::validateDate(int year, int month, int day, int hour, int min)
	{
		if (year < MIN_YEAR || year > MAX_YEAR)
		{
			setError("Invalid Year");
		}
		else if (month < 1 || month > 12)
		{
			setError("Invalid Month");
		}
		else if (day < 1 || day > daysOfMonth(year, month))
		{
			setError("Invalid Day");
		}
		else if (hour < 0 || hour > 23)
		{
			setError("Invalid Hour");
		}
		else if (min < 0 || min > 59)
		{
			setError("Invlid Minute");
		}
	}

	
	void Date::setError(const char* errorMessage)
	{
		Error validationError(errorMessage);
		Err = validationError;
	}

	
	bool Date::operator==(const Date& right) const
	{
		if (m_year == right.m_year && m_month == right.m_month && m_day == right.m_day && hour == right.hour && minute == right.minute)
			return true;
		else return false;
	}

	bool Date::operator!=(const Date& right) const
	{
		if (m_year == right.m_year && m_month == right.m_month && m_day == right.m_day && hour == right.hour && minute == right.minute)
			return false;

		else {
			return true;
		}
	}

	bool Date::operator>(const Date& right) const
	{
		if (m_year > right.m_year ||
			(m_year == right.m_year && m_month > right.m_month) ||
			(m_year == right.m_year && m_month == right.m_month && m_day > right.m_day) ||
			(m_year == right.m_year && m_month == right.m_month && m_day == right.m_day && hour > right.hour) ||
			(m_year == right.m_year && m_month == right.m_month && m_day == right.m_day && hour == right.hour && minute > right.minute))
			return true;
		else {
			return false;
		}
	}

	bool Date::operator<(const Date& right) const
	{
		if (m_year < right.m_year ||
			(m_year == right.m_year && m_month < right.m_month) ||
			(m_year == right.m_year && m_month == right.m_month && m_day < right.m_day) ||
			(m_year == right.m_year && m_month == right.m_month && m_day == right.m_day && hour < right.hour) ||
			(m_year == right.m_year && m_month == right.m_month && m_day == right.m_day && hour == right.hour && minute < right.minute))
			return true;
		else {
			return false;
		}
	}

	bool Date::operator>=(const Date& right) const
	{
		if ((*this > right) || (*this == right))
			return true;
		else {
			return false;
		}
	}

	bool Date::operator<=(const Date& right) const
	{
		if ((*this < right) || (*this == right))
			return true;
		else {
			return false;
		}
	}

	Date& Date::dateOnly(bool dateOnlyFlag)
	{
		dateOnlyValue = dateOnlyFlag;
		if (dateOnlyFlag)
		{
			hour = 0;
			minute = 0;
		}
		return *this;
	}

	
	Date::operator bool() const
	{
		return !Err;
	}

	
	const Error& Date::error() const
	{
		return Err;
	}

	
	istream& Date::read(istream& istr)
	{
		string errorMsg;

		this->Err.clear();
		this->setDate(0, 0, 0, 0, 0);

		istr >> m_year;
		if (!istr) errorMsg = "Cannot read year entry";

		istr.ignore();

		istr >> m_month;
		if (errorMsg.empty() && !istr) errorMsg = "Cannot read month entry";
		istr.ignore();

		istr >> m_day;
		if (errorMsg.empty() && !istr) errorMsg = "Cannot read day entry";


		if (!dateOnlyValue)
		{
			istr.ignore();
			istr >> hour;
			if (errorMsg.empty() && !istr) errorMsg = "Cannot read hour entry";

			istr.ignore();

			istr >> minute;
			if (errorMsg.empty() && !istr) errorMsg = "Cannot read minute entry";
		}

		if (errorMsg.empty())
		{
			validateDate(this->m_year, this->m_month, this->m_day, this->hour, this->minute);

		}
		else
		{
			setError(errorMsg.c_str());
		}

		return istr;
	}

	
	ostream& Date::display(ostream& ostr) const
	{
		if (Err)
		{
			ostr << Err << "(" << m_year << "/";
			ostr << setw(2) << setfill('0') << m_month << "/";
			ostr << setw(2) << setfill('0') << m_day;

			if (!dateOnlyValue)
			{
				ostr << ", ";
				ostr << setw(2) << setfill('0') << hour << ":";
				ostr << setw(2) << setfill('0') << minute;
			}
			ostr << ")";
		}
		else
		{
			ostr << m_year << "/";
			ostr << setw(2) << setfill('0') << m_month << "/";
			ostr << setw(2) << setfill('0') << m_day;
			if (!dateOnlyValue)
			{
				ostr << ", ";
				ostr << setw(2) << setfill('0') << hour << ":";
				ostr << setw(2) << setfill('0') << minute;
			}
		}
		return ostr;
	}

	
	ostream& operator<<(ostream& ostr, const Date& myDate)
	{
		myDate.display(ostr);
		return ostr;
	}

	istream& operator>>(istream& istr, Date& myDate)
	{
		myDate.read(istr);
		return istr;
	}

}