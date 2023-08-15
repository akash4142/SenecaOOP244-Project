/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/

#ifndef SDDS_NPERISHABLE_H_
#define SDDS_PERISHABLE_H_
#include <iostream>
#include "Item.h"
#include "Date.h"

using namespace std;
namespace sdds {
    class Perishable : public Item {
        Date m_date;
        char itemType() const override {
            return 'P';
        }

        ostream& write(ostream& os) const override;
        istream& read(istream& is) override;
        ofstream& save(ofstream& of) const override;
        ifstream& load(ifstream& ifs) override;
    };
}

#endif //!SDDS_PERISHABLE_H_