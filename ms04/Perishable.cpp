/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include <iomanip>
#include <iostream>
#include "Perishable.h"

namespace sdds {

    std::ostream& Perishable::write(std::ostream& os) const {
        Item::write(os);
        if (*this) {
            if (m_displayType == POS_LIST) {
                os << "  " << m_date << " |";
            }
            else {
                os << "Expiry date: " << m_date << std::endl;
                os << "=============^" << std::endl;
            }
        }

        return os;
    }

    std::istream& Perishable::read(std::istream& is) {
        Item::read(is);

        if (1) {
            Date date;
            date.dateOnly(true);
            std::cout << "Expiry date (YYYY/MM/DD)" << std::endl << "> ";
            is >> date;
            if (date) {
                m_date = date;
            }
            else {
                m_error = date.error();
            }
        }

        return is;
    }

    std::ofstream& Perishable::save(std::ofstream& of) const {
        Item::save(of);

        if (*this) {
            of << "," << m_date;
        }

        return of;
    }

    std::ifstream& Perishable::load(std::ifstream& ifs) {
        Item::load(ifs);

        if (*this && !ifs.fail()) {
            Date date;
            date.dateOnly(true);
            char ig;
            ifs >> ig;
            ifs >> date;
            if (date) {
                m_date = date;
            }
            else {
                m_error = date.error();
            }
        }

        return ifs;
    }

}