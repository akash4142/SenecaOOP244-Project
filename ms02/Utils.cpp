/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include "Utils.h"
namespace sdds {
    void getSystemDate(int& m_year, int& month, int& m_day, int& hour, int& min, bool dateOnly) {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        m_day = lt.tm_mday;
        month = lt.tm_mon + 1;
        m_year = lt.tm_year + 1900;
        if (dateOnly) {
            hour = min = 0;
        }
        else {
            hour = lt.tm_hour;
            min = lt.tm_min;
        }
    }
    int uniqueDateValue(int m_year, int month, int m_day, int hour, int min) {
        return m_year * 535680 + month * 44640 + m_day * 1440 + hour * 60 + min;
    }

    int daysOfMonth(int m_year, int m_month) {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int month = m_month >= 1 && m_month <= 12 ? m_month : 13;
        month--;
        return days[month] + int((month == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
    }
}