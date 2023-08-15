/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#ifndef SDDS_POSIO_H_
#define SDDS_POSIO_H_
#include <iostream>

namespace sdds {
    class PosIO {
    public:
        virtual ~PosIO() {}
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;
        virtual std::ofstream& save(std::ofstream& of) const = 0;
        virtual std::ifstream& load(std::ifstream& ifs) = 0;
    };

    std::ostream& operator<<(std::ostream& os, const PosIO& pos);
    std::ofstream& operator<<(std::ofstream& of, const PosIO& pos);
    std::istream& operator>>(std::istream& in, PosIO& pos);
    std::ifstream& operator>>(std::ifstream& ifs, PosIO& pos);
}
#endif 