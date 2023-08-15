/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include "Date.h"
#include "Utils.h"
#include "POS.h"
#include <iostream>
#include <iomanip>
namespace sdds
{
    Date::Date() {
        getSystemDate(m_year, m_month, m_day, m_hour, m_min, false);
    }

    Date::Date(int year, int month, int day) {
        m_year = year;
        m_month = month;
        m_day = day;
        dateOnly(true);
        validate();
    }

    Date::Date(int year, int month, int day, int hour, int min) {
        m_year = year;
        m_month = month;
        m_day = day;
        m_hour = hour;
        m_min = min;
        dateOnly(false);
        validate();
    }

    bool Date::operator ==(const Date& other) const {
        int ourValue = uniqueDateValue(m_year, m_month, m_day, m_hour, m_min);
        int otherValue = uniqueDateValue(other.m_year, other.m_month, other.m_day, other.m_hour, other.m_min);
        return ourValue == otherValue;
    }

    bool Date::operator !=(const Date& other) const {
        int ourValue = uniqueDateValue(m_year, m_month, m_day, m_hour, m_min);
        int otherValue = uniqueDateValue(other.m_year, other.m_month, other.m_day, other.m_hour, other.m_min);
        return ourValue != otherValue;
    }

    bool Date::operator <(const Date& other) const {
        int ourValue = uniqueDateValue(m_year, m_month, m_day, m_hour, m_min);
        int otherValue = uniqueDateValue(other.m_year, other.m_month, other.m_day, other.m_hour, other.m_min);
        return ourValue < otherValue;
    }

    bool Date::operator >(const Date& other) const {
        int ourValue = uniqueDateValue(m_year, m_month, m_day, m_hour, m_min);
        int otherValue = uniqueDateValue(other.m_year, other.m_month, other.m_day, other.m_hour, other.m_min);
        return ourValue > otherValue;
    }

    bool Date::operator <=(const Date& other) const {
        int ourValue = uniqueDateValue(m_year, m_month, m_day, m_hour, m_min);
        int otherValue = uniqueDateValue(other.m_year, other.m_month, other.m_day, other.m_hour, other.m_min);
        return ourValue <= otherValue;
    }

    bool Date::operator >=(const Date& other) const {
        int ourValue = uniqueDateValue(m_year, m_month, m_day, m_hour, m_min);
        int otherValue = uniqueDateValue(other.m_year, other.m_month, other.m_day, other.m_hour, other.m_min);
        return ourValue >= otherValue;
    }

    bool Date::operator !() const {
        return m_err;
    }

    Date& Date::dateOnly(bool value) {
        m_dateOnly = value;

        if (value == true) {
            m_hour = 0;
            m_min = 0;
        }
        return *this;
    }

    const Error& Date::error() const {
        return m_err;
    }


    void Date::validate() {
        if (m_year < MIN_YEAR || m_year > MAX_YEAR) m_err = "Invalid Year";
        else if (m_month < 1 || m_month > 12) m_err = "Invalid Month";
        else if (m_day < 1 || m_day > daysOfMonth(m_year, m_month)) m_err = "Invalid Day";
        else if (m_hour < 0 || m_hour > 23) m_err = "Invalid Hour";
        else if (m_min < 0 || m_min > 59) m_err = "Invalid Minute";
    }

    std::ostream& Date::write(std::ostream& os) const {
        if (m_err) {
            os << m_err << "(";
        }

        os << m_year << "/"
            << std::setw(2) << std::setfill('0') << std::right << m_month << "/"
            << std::setw(2) << std::setfill('0') << std::right << m_day;
        os << std::left;

        if (m_dateOnly == false) {
            os << ", " << std::setw(2) << std::setfill('0') << std::right << m_hour
                << ":" << std::setw(2) << std::setfill('0') << std::right << m_min;
            os << std::left;
        }

        if (m_err) {
            os << ")";
        }

        os << std::setfill(' ');
        return os;
    }

    std::istream& Date::read(std::istream& is) {
        m_err.clear();
        m_year = 0;
        m_month = 0;
        m_day = 0;
        m_hour = 0;
        m_min = 0;

        char temp;

        is >> m_year >> temp;
        if (is.fail()) {
            m_err = "Cannot read year entry";
            return is;
        }

        is >> m_month >> temp;
        if (is.fail()) {
            m_err = "Cannot read month entry";
            return is;
        }

        is >> m_day;
        if (is.fail()) {
            m_err = "Cannot read day entry";
            return is;
        }

        if (is.peek() == '\n') {
            m_dateOnly = true;
            validate();
            return is;
        };

        is >> temp;

        is >> m_hour >> temp;
        if (is.fail()) {
            m_err = "Cannot read hour entry";
            return is;
        }

        is >> m_min;
        if (is.fail()) {
            m_err = "Cannot read minute entry";
            return is;
        }

        validate();
        return is;
    }

    std::ostream& operator<< (std::ostream& os, const Date& date) {
        return date.write(os);
    }
    std::istream& operator>> (std::istream& is, Date& date) {
        return date.read(is);
    }

}
