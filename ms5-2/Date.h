/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include "Error.h"
#include <iostream>
#include "Utils.h"
namespace sdds
{
    class Date
    {
    private:
        int m_year = 0;
        int m_month = 0;
        int m_day = 0;
        int m_hour = 0;
        int m_min = 0;
        bool m_dateOnly = false;
        Error m_err;
        void validate();
    public:
        Date();
        Date(int year, int month, int day);
        Date(int year, int month, int day, int hour, int min = 0);
        bool operator ==(const Date& other) const;
        bool operator !=(const Date& other) const;
        bool operator <(const Date& other) const;
        bool operator >(const Date& other) const;
        bool operator <=(const Date& other) const;
        bool operator >=(const Date& other) const;
        bool operator !() const;
        Date& dateOnly(bool value);
        const Error& error() const;
        
        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);
    };
    std::ostream& operator<< (std::ostream& os, const Date& date);
    std::istream& operator>> (std::istream& is, Date& date);
}

#endif