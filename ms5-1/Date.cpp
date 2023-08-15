/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include <iomanip>
#include "Date.h"
#include "Utils.h"
#include "POS.h"

namespace sdds {

    bool Date::validate() {
        if (m_year < MIN_YEAR || m_year > MAX_YEAR) {
            m_error = Error("Invalid Year");
            return false;
        }

        if (m_month < 1 || m_month > 12) {
            m_error = Error("Invalid Month");
            return false;
        }

        if (m_day < 1 || m_day > daysOfMonth(m_year, m_month)) {
            m_error = Error("Invalid Day");
            return false;
        }

        if (m_hour < 0 || m_hour > 23) {
            m_error = Error("Invalid Hour");
            return false;
        }

        if (m_minute < 0 || m_minute > 59) {
            m_error = Error("Invalid Minute");
            return false;
        }

        return true;
    }

    Date::Date() {
        m_onlyDate = false;
        getSystemDate(m_year, m_month, m_day, m_hour, m_minute, m_onlyDate);
    }

    Date::Date(int year, int month, int day) : m_year(year), m_month(month), m_day(day) {
        m_onlyDate = true;
        validate();
    }

    Date::Date(int year, int month, int day, int hour, int minute)
        : m_year(year), m_month(month), m_day(day), m_hour(hour), m_minute(minute) {
        m_onlyDate = false;
        validate();
    }

    Date::operator bool() const {
        return !(m_error);
    }

    Date& Date::dateOnly(bool val) {
        m_onlyDate = val;
        if (m_onlyDate) {
            m_hour = m_minute = 0;
        }

        return *this;
    }

    void Date::display(std::ostream& out) const {
        out.fill('0');
        if (*this) {
            out << m_year << "/";
            out << std::right << std::setw(2) << m_month << "/" << std::setw(2) << m_day;
            if (!m_onlyDate)
                out << ", " << std::setw(2) << m_hour << ":" << std::setw(2) << m_minute;
        }
        else {
            out << m_error << "(" << m_year << "/" << std::setw(2) << m_month << "/" << std::setw(2) << m_day;
            if (!m_onlyDate)
                out << ", " << std::setw(2) << m_hour << ":" << std::setw(2) << m_minute;
            out << ")";
        }
        out.fill(' ');
        out << std::left;
    }

    void Date::read(std::istream& in) {
        char tmp = 0;
        m_error.clear();
        m_year = m_month = m_day = m_hour = m_minute = 0;
        in >> m_year;
        if (in.fail()) {
            m_error = Error("Cannot read year entry");
            return;
        }
        in >> tmp;
        in >> m_month;
        if (in.fail()) {
            m_error = Error("Cannot read month entry");
            return;
        }
        in >> tmp;
        in >> m_day;
        if (in.fail()) {
            m_error = Error("Cannot read day entry");
            return;
        }

        if (m_onlyDate) {
            validate();
            return;
        }

        in >> tmp;
        in >> m_hour;
        if (in.fail()) {
            m_error = Error("Cannot read hour entry");
            return;
        }
        in >> tmp;
        in >> m_minute;
        if (in.fail()) {
            m_error = Error("Cannot read minute entry");
            return;
        }

        validate();
    }

    bool Date::operator<(const Date& d) const {
        int l = uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute);
        int r = uniqueDateValue(d.m_year, d.m_month, d.m_day, d.m_hour, d.m_minute);
        return l < r;
    }

    bool Date::operator>(const Date& d) const {
        return d < *this;
    }

    bool Date::operator<=(const Date& d) const {
        return !(*this > d);
    }

    bool Date::operator>=(const Date& d) const {
        return !(*this < d);
    }

    bool Date::operator==(const Date& d) const {
        int l = uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute);
        int r = uniqueDateValue(d.m_year, d.m_month, d.m_day, d.m_hour, d.m_minute);
        return l == r;
    }

    bool Date::operator!=(const Date& d) const {
        return !(*this == d);
    }

    std::ostream& operator<<(std::ostream& out, const Date& date) {
        date.display(out);
        return out;
    }

    std::istream& operator>>(std::istream& in, Date& date) {
        date.read(in);
        return in;
    }

}