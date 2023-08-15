/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include "PosIO.h"

namespace sdds
{

    std::ostream& operator<<(std::ostream& os, const PosIO& obj) {
        obj.write(os);
        return os;
    }


    std::ofstream& operator<<(std::ofstream& ofs, const PosIO& obj) {
        obj.save(ofs);
        return ofs;
    }


    std::istream& operator>>(std::istream& is, PosIO& obj) {
        obj.read(is);
        return is;
    }


    std::ifstream& operator>>(std::ifstream& ifs, PosIO& obj) {
        obj.load(ifs);
        return ifs;
    }
}
