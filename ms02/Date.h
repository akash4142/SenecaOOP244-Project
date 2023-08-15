/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
#include "POS.h"
#include "Error.h"
#include "Utils.h"


namespace sdds
{
    class Date
    {
        int m_year;
        int m_month;
        int m_day;
        int hour;
        int minute;
        bool dateOnlyValue;
        Error Err;
        void validateDate(int year, int month, int day, int hour, int min);
        void setError(const char* errorMessage);

    public:
        Date();
        Date(int m_year, int m_month, int m_day, int hour = 0, int minute = 0);

        void setDate(const int m_year, const int m_month, const int m_day, const int hour, const int minute);

        bool operator==(const Date& right) const;
        bool operator!=(const Date& right) const;
        bool operator>(const Date& right) const;
        bool operator<(const Date& right) const;
        bool operator>=(const Date& right) const;
        bool operator<=(const Date& right) const;

        Date& dateOnly(bool dateOnlyFlag = true);
        operator bool() const;
        const Error& error() const;

        std::istream& read(std::istream& istr);
        std::ostream& display(std::ostream& ostr) const;
    };

    std::ostream& operator<<(std::ostream& os, const Date& d);
    std::istream& operator>>(std::istream& is, Date& d);
  
}

#endif 