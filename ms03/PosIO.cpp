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
#include "PosIO.h"

using namespace std;

namespace sdds
{

	ostream& operator <<(ostream& ostr, PosIO& right)
	{
		right.write(ostr);
		return ostr;
	}

	istream& operator >>(istream& istr, PosIO& right)
	{
		right.read(istr);
		return istr;
	}

	ofstream& operator <<(ofstream& ofstr, PosIO& right)
	{
		right.save(ofstr);
		return ofstr;
	}

	ifstream& operator >>(ifstream& ifstr, PosIO& right)
	{
		right.load(ifstr);
		return ifstr;
	}

}