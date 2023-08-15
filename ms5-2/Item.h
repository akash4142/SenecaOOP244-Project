/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_ITEM_H_
#define SDDS_ITEM_H_
#include <iostream>
#include <fstream>
#include "POS.h"
#include "Error.h"
#include "PosIO.h"

namespace sdds
{
    class Item : public PosIO
    {
    private:
        char* m_SKU = nullptr;
        char* m_name = nullptr;
        double m_price = 0;
        bool m_taxed = true;
        int m_qty = 0;
    protected:
        int m_displayType = POS_LIST;
        Error m_err;
    public:
        Item() {};
        Item(const Item& other);
        Item& operator =(const Item& other);
        ~Item();
        bool operator==(const char* other) const;
        bool operator>(const Item& other) const;
        int operator+=(const int qty);
        int operator-=(const int qty);
        operator bool() const;
        virtual char itemType() const = 0;
        const char* getName() const;
        const char* getSKU() const;
        Item& displayType(int dType);
        double cost() const;
        int quantity() const;
        Item& clear();
        std::ostream& bprint(std::ostream& os) const;
        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);
        std::ofstream& save(std::ofstream& ofs) const;
        std::ifstream& load(std::ifstream& ifs);
    };
    double operator+=(double& num, const Item& item);
} 


#endif 