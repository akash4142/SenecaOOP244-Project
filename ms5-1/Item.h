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
using namespace std;
namespace sdds {
    class Item : public PosIO {
        char m_SKU[MAX_SKU_LEN + 1];
        char* m_name;
        double m_price;
        bool m_taxed;
        int m_quantity;

    protected:
        int m_displayType;
        Error m_error;

    public:
        Item();
        ~Item();
        Item(const Item& item);
        Item& operator=(const Item& item);

        Item& displayType(int val);
        double cost() const;
        int quantity() const;
        Item& clear();
        char * name();
        bool operator==(const char* str) const;
        bool operator>(const Item& item) const;
        int operator+=(int q);
        int operator-=(int q);

        operator bool() const;

        virtual char itemType() const = 0;

        ostream& write(ostream& os) const override;
        istream& read(istream& is) override;
        ofstream& save(ofstream& of) const override;
        ifstream& load(ifstream& ifs) override;
        ostream& bprint(ostream& os) const;
    };

    double operator+=(double v, const Item& item);
}

#endif //!SDDS_ITEM_H_