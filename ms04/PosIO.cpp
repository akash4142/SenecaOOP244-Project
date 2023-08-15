/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include "PosIO.h"

namespace sdds {

    std::ostream& operator<<(std::ostream& os, const PosIO& pos) {
        return pos.write(os);
    }

    std::ofstream& operator<<(std::ofstream& of, const PosIO& pos) {
        return pos.save(of);
    }

    std::istream& operator>>(std::istream& is, PosIO& pos) {
        return pos.read(is);
    }

    std::ifstream& operator>>(std::ifstream& ifs, PosIO& pos) {
        return pos.load(ifs);
    }

}