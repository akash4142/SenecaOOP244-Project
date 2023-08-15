/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/

#ifndef SDDS_NONPERISHABLE_H_
#define SDDS_NONPERISHABLE_H_
#include <iostream>
#include "Item.h"
using namespace std;
namespace sdds {
    class NonPerishable : public Item {
        char itemType() const override {
            return 'N';
        }

        ostream& write(ostream& os) const override;
    };
}

#endif //!SDDS_NONPERISHABLE_H_