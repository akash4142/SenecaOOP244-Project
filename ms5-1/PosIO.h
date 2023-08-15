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
using namespace std;
namespace sdds {
    class PosIO {
    public:
        virtual ~PosIO() {}
        virtual ostream& write(ostream& os) const = 0;
        virtual istream& read(istream& is) = 0;
        virtual ofstream& save(ofstream& of) const = 0;
        virtual ifstream& load(ifstream& ifs) = 0;
    };

    ostream& operator<<(ostream& os, const PosIO& pos);
    ofstream& operator<<(ofstream& of, const PosIO& pos);
    istream& operator>>(istream& in, PosIO& pos);
    ifstream& operator>>(ifstream& ifs, PosIO& pos);
}
#endif //!SDDS_POSIO_H_