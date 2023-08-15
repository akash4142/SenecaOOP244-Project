/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include <iomanip>
#include "NonPerishable.h"

namespace sdds {

    std::ostream& NonPerishable::write(std::ostream& os) const {
        Item::write(os);
        if (*this) {
            if (m_displayType == POS_LIST) {
                os << "     N / A   |";
            }
            else {
                os << "=============^" << std::endl;
            }
        }

        return os;
    }

}