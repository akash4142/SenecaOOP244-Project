/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

namespace sdds {
	void getSystemDate(int& m_year, int& month, int& m_day, int& hour, int& min, bool dateOnly);
	int uniqueDateValue(int m_year, int month, int m_day, int hour, int min);
	int daysOfMonth(int m_year, int m_month);
}
#endif 