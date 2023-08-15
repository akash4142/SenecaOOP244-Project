/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include <iostream>
#include <fstream>
#include "Item.h"
#include "Date.h"
#include "POS.h"
namespace sdds
{
    class Perishable :public Item
    {
        sdds::Date m_expirydate;
    public:
        char itemType() const;
        std::istream& read(std::istream& is);
        std::ostream& write(std::ostream& os) const;
        std::ifstream& load(std::ifstream& ifs);
        std::ofstream& save(std::ofstream& ofs) const;
    };


}
#endif