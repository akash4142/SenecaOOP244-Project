#define _CRT_SECURE_NO_WARNINGS
/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <string>
#include "Item.h"

namespace sdds {

    Item::Item() {
        m_name = NULL;
        m_price = 0.0;
        m_quantity = -1;
    }

    Item::~Item() {
        if (m_name)
            delete[] m_name;
        m_name = NULL;
    }

    Item::Item(const Item& item) {
        if (item.m_name) {
            int len = strlen(item.m_name);
            if (len > 0) {
                m_name = new char[len];
                strcpy(m_name, item.m_name);
            }
        }
        m_price = item.m_price;
        m_quantity = item.m_quantity;
        strcpy(m_SKU, item.m_SKU);
        m_taxed = item.m_taxed;
        m_displayType = item.m_displayType;
        m_error = item.m_error;
    }

    Item& Item::operator=(const Item& item) {
        if (m_name) {
            delete[] m_name;
            m_name = NULL;
        }

        if (item.m_name) {
            int len = strlen(item.m_name);
            if (len > 0) {
                m_name = new char[len + 1];
                strcpy(m_name, item.m_name);
            }
        }
        m_price = item.m_price;
        m_quantity = item.m_quantity;
        strcpy(m_SKU, item.m_SKU);
        m_taxed = item.m_taxed;
        m_displayType = item.m_displayType;
        m_error = item.m_error;

        return *this;
    }

    bool Item::operator==(const char* str) const {
        return atoi(str) == atoi(m_SKU);
    }

    bool Item::operator>(const Item& item) const {
        return atoi(m_SKU) > atoi(item.m_SKU);
    }

    int Item::operator+=(int q) {
        m_quantity += q;
        if (m_quantity > MAX_STOCK_NUMBER) {
            m_quantity = MAX_STOCK_NUMBER;
            m_error = Error(ERROR_POS_QTY);
        }
        return m_quantity;
    }

    int Item::operator-=(int q) {
        m_quantity -= q;
        if (m_quantity < 0) {
            m_quantity = 0;
            m_error = Error(ERROR_POS_STOCK);
        }
        return m_quantity;
    }

    Item::operator bool() const {
        return !(m_error);
    }

    double operator+=(double val, const Item& item) {
        val = val + item.cost() * (double)item.quantity();
        return val;
    }

    Item& Item::displayType(int type) {
        m_displayType = type;
        return *this;
    }

    double Item::cost() const {
        if (m_taxed)
            return m_price + (m_price * TAX);
        return m_price;
    }

    int Item::quantity() const {
        return m_quantity;
    }
    char * Item::name() {
        return m_name;
    }

    Item& Item::clear() {
        if (m_error)
            m_error.clear();

        return *this;
    }

    std::ostream& Item::write(std::ostream& os) const {
        if (m_error) {
            os << m_error;
        }

        else if (m_displayType == POS_LIST) {
            os << std::left << std::setw(7) << m_SKU << "|";
            for (int i = 0; i < 20; i++) {
                if (m_name && i < (int)strlen(m_name) && m_name[i])
                    os << m_name[i];
                else
                    os << ' ';
            }
            os << '|';
            os << std::fixed << std::setprecision(2) << std::right << std::setw(7) << m_price << '|';
            os << " ";
            if (m_taxed)
                os << "X";
            else
                os << " ";
            os << " |";
            os << std::right << std::setw(4) << m_quantity << '|';
            os << std::right << std::setw(9) << cost() * quantity() << '|';

            /* reset ostream to left */
            os << std::left;
        }

        else if (m_displayType == POS_FORM) {
            os << "=============v" << std::endl;
            os << "Name:        " << m_name << std::endl;
            os << "Sku:         " << m_SKU << std::endl;
            os << "Price:       " << m_price << std::endl;
            os << "Price + tax: ";
            if (!m_taxed)
                os << "N/A";
            else
                os << cost();
            os << std::endl;
            os << "Stock Qty:   " << m_quantity;
            os << '\n';
        }

        return os;
    }

    std::istream& Item::read(std::istream& is) {
        clear();

        if (m_name) {
            delete[] m_name;
            m_name = NULL;
        }

        char tmp[100];
        std::cout << "Sku" << std::endl << "> ";
        is >> tmp;

        while (strlen(tmp) > MAX_SKU_LEN) {
            std::cout << ERROR_POS_SKU << std::endl << "> ";
            is >> tmp;
        }

        strcpy(m_SKU, tmp);
        memset(tmp, '\0', 100);

        std::cout << "Name" << std::endl << "> ";
        is.ignore(1000, '\n');
        is.getline(tmp, 100);

        while (strlen(tmp) > MAX_NAME_LEN) {
            std::cout << ERROR_POS_NAME << std::endl << "> ";
            is.getline(tmp, 100);
        }

        m_name = new char[strlen(tmp) + 1];
        strcpy(m_name, tmp);

        double val = -1;
        std::cout << "Price" << std::endl << "> ";
        is >> val;

        while (val < 0 || is.fail()) {
            if (is.fail()) {
                is.clear();
                is.ignore(10000, '\n');
            }
            std::cout << ERROR_POS_PRICE << std::endl << "> ";
            is >> val;
        }

        m_price = val;

        char tmpchar = 0;
        std::cout << "Taxed?" << std::endl << "(Y)es/(N)o: ";
        is >> tmpchar;

        while ((tmpchar != 'Y' && tmpchar != 'y' && tmpchar != 'N' && tmpchar != 'n') || is.fail()) {
            if (is.fail()) {
                is.clear();
            }
            is.ignore(10000, '\n');
            std::cout << "Only 'y' and 'n' are acceptable: ";
            is >> tmpchar;
        }

        if (tmpchar == 'Y' || tmpchar == 'y')
            m_taxed = true;
        else
            m_taxed = false;

        std::cout << "Quantity" << std::endl << "> ";
        is >> val;

        while (val <= 0 || val > 99 || is.fail()) {
            if (is.fail()) {
                is.clear();
                is.ignore(10000, '\n');
            }
            std::cout << ERROR_POS_QTY << std::endl << "> ";
            is >> val;
        }

        m_quantity = val;
        return is;
    }

    std::ofstream& Item::save(std::ofstream& ofs) const {
        if (m_error) {
            std::cerr << m_error << '\n';
            return ofs;
        }

        ofs << itemType() << ',';
        ofs << m_SKU << ',';
        ofs << m_name << ',';
        ofs << std::fixed << std::setprecision(2) << m_price << ',';
        ofs << m_taxed << ',';
        ofs << m_quantity;
        return ofs;
    }

    std::ifstream& Item::load(std::ifstream& ifs) {
        clear();

        if (m_name) {
            delete[] m_name;
            m_name = NULL;
        }

        char tmp[100];
        char ig = 0;

        if (ifs.fail())
            return ifs;

        int tval = 0;
        ifs >> tval;
        sprintf(tmp, "%d", tval);
        if (strlen(tmp) > MAX_SKU_LEN) {
            m_error = Error(ERROR_POS_SKU);
            return ifs;
        }
        else {
            strcpy(m_SKU, tmp);
        }

        ifs >> ig;

        ifs.getline(tmp, 100, ',');
        if (strlen(tmp) > MAX_NAME_LEN) {
            m_error = Error(ERROR_POS_NAME);
            return ifs;
        }
        else {
            m_name = new char[strlen(tmp) + 1];
            strcpy(m_name, tmp);
        }

        double val = 0;
        ifs >> val;
        if (val > 0) {
            m_price = val;
        }
        else {
            m_error = Error(ERROR_POS_PRICE);
            return ifs;
        }

        ifs >> ig;

        int taxed;
        ifs >> taxed;

        if (taxed > 1 || taxed < 0) {
            m_error = Error(ERROR_POS_TAX);
            return ifs;
        }

        m_taxed = taxed > 0;
        ifs >> ig;

        int quantity = 0;
        ifs >> quantity;
        if (quantity < 0 || quantity > 99) {
            m_error = Error(ERROR_POS_QTY);
            return ifs;
        }
        else {
            m_quantity = quantity;
        }

        return ifs;
    }

    std::ostream& Item::bprint(std::ostream& os) const {
        os << "| ";
        for (int i = 0; i < 20; i++) {
            if (m_name && i < (int)strlen(m_name) && m_name[i])
                os << m_name[i];
            else
                os << ' ';
        }

        os << "| ";
        os << std::fixed << std::setprecision(2) << std::right << std::setw(9) << cost();
        os << " |  ";
        if (m_taxed)
            os << "T";
        else
            os << " ";
        os << "  |" << '\n';

        return os;
    }

}
