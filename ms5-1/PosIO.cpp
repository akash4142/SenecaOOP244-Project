/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include "PosIO.h"
using namespace std;
namespace sdds {

  ostream& operator<<(ostream& os, const PosIO& pos) {
        return pos.write(os);
    }

  ofstream& operator<<(ofstream& of, const PosIO& pos) {
        return pos.save(of);
    }

    istream& operator>>(istream& is, PosIO& pos) {
        return pos.read(is);
    }

    ifstream& operator>>(ifstream& ifs, PosIO& pos) {
        return pos.load(ifs);
    }

}