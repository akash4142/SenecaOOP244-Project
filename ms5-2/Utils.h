/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
#include <ctime>
namespace sdds
{
    void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);
    int daysOfMonth(int year, int month);
    int uniqueDateValue(int year, int mon, int day, int hour, int min);
}

#endif