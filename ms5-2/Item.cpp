#define _CRT_SECURE_NO_WARNINGS
/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include "Item.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include "PosIO.h"
#include "POS.h"
namespace sdds
{
    Item::Item(const Item& other) {
        *this = other;
    }
    Item& Item::operator =(const Item& other) {
        delete[] m_SKU;
        m_SKU = nullptr;
        delete[] m_name;
        m_name = nullptr;

        if (other.m_SKU != nullptr && other.m_SKU[0] != '\0') {
            m_SKU = new char[std::strlen(other.m_SKU) + 1];
            std::strncpy(m_SKU, other.m_SKU, std::strlen(other.m_SKU) + 1);
        }

        if (other.m_name != nullptr && other.m_name[0] != '\0') {
            m_name = new char[std::strlen(other.m_name) + 1];
            std::strncpy(m_name, other.m_name, std::strlen(other.m_name) + 1);
        }

        m_price = other.m_price;
        m_taxed = other.m_taxed;
        m_qty = other.m_qty;
        m_displayType = other.m_displayType;
        m_err = other.m_err;

        return *this;
    }
    Item::~Item() {
        delete[] m_SKU;
        delete[] m_name;
    }

    bool Item::operator==(const char* other) const {
        return std::strcmp(m_SKU, other) == 0;
    }

    bool Item::operator>(const Item& other) const {
        return std::strcmp(m_SKU, other.m_SKU) > 0;
    }

    int Item::operator+=(const int qty) {
        if (m_qty + qty > MAX_STOCK_NUMBER) {
            m_qty = MAX_STOCK_NUMBER;
            m_err = ERROR_POS_QTY;
        }
        else {
            m_qty += qty;
        }

        return m_qty;
    }

    int Item::operator-=(const int qty) {
        if (m_qty - qty < 0) {
            m_qty = 0;
            m_err = ERROR_POS_STOCK;
        }
        else {
            m_qty -= qty;
        }

        return m_qty;
    }

    Item::operator bool() const {
        return !m_err;
    }

    Item& Item::displayType(int dType) {
        if (dType == POS_LIST) m_displayType = POS_LIST;
        else if (dType == POS_FORM) m_displayType = POS_FORM;
        return *this;
    }

    double Item::cost() const {
        if (m_taxed) return m_price + (m_price * TAX);
        else return m_price;
    }

    int Item::quantity() const {
        return m_qty;
    }
    Item& Item::clear() {
        m_err.clear();
        return *this;
    }

    std::ostream& Item::write(std::ostream& os) const {
        if (m_err) {
            os << m_err;
            return os;
        }
        if (m_displayType == POS_LIST) {
            os << std::setw(7) << std::left << m_SKU << "|";
            std::string name = m_name;
            os << std::left << std::setw(20) << name.substr(0, 20) << "|";
            os << std::setw(7) << std::right << std::fixed << std::setprecision(2) << m_price << "|";
            os << " ";
            if (m_taxed) os << "X";
            else os << " ";
            os << " |";
            os << std::setw(4) << std::right << m_qty << "|";
            os << std::setw(9) << std::right << cost() * m_qty << "|";
            os << std::left;
        }
        else {
            os << "=============v\n";
            os << std::setw(13) << std::left << "Name:" << m_name << "\n"
                << std::setw(13) << std::left << "Sku:" << m_SKU << "\n"
                << std::setw(13) << std::left << "Price:" << std::fixed << std::setprecision(2) << m_price << "\n"
                << std::setw(13) << std::left << "Price + tax:";

            if (!m_taxed) os << "N/A\n";
            else os << std::fixed << std::setprecision(2) << m_price + (m_price * TAX) << "\n";
            os << std::setw(13) << std::left << "Stock Qty:" << m_qty << "\n";
        }
        return os;
    }

    std::ofstream& Item::save(std::ofstream& ofs) const {
        if (m_err) {
            std::cerr << m_err;
            return ofs;
        }
        ofs << itemType() << "," << m_SKU << "," << m_name << "," << std::fixed << std::setprecision(2) << m_price << ",";
        if (m_taxed) ofs << "1,";
        else ofs << "0,";
        ofs << m_qty;

        return ofs;
    }

    std::istream& Item::read(std::istream& is) {
        m_err.clear();
        std::string SKU;
        std::cout << "Sku\n";
        while (true) {
            std::cout << "> ";
            is >> SKU;
            if (SKU.length() > MAX_SKU_LEN) {
                std::cout << ERROR_POS_SKU << "\n";
            }
            else break;
        }
        delete[] m_SKU;
        m_SKU = new char[SKU.length() + 1];
        std::strcpy(m_SKU, SKU.c_str());

        std::string name;
        std::cout << "Name\n";
        is.ignore();
        while (true) {
            std::cout << "> ";
            std::getline(is, name);
            if (name.length() > MAX_NAME_LEN) {
                std::cout << ERROR_POS_NAME << "\n";
            }
            else break;
        }

        delete[] m_name;
        m_name = new char[name.length() + 1];
        std::strcpy(m_name, name.c_str());

        double price;
        std::cout << "Price\n";
        while (true) {
            std::cout << "> ";
            std::cin >> price;
            if (std::cin.fail() || price < 0) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << ERROR_POS_PRICE << "\n";
            }
            else {
                std::cin.ignore(1000, '\n');
                break;
            }
        }
        m_price = price;

        std::string taxed;
        std::cout << "Taxed?\n(Y)es/(N)o";
        while (true) {
            std::cout << ": ";
            is >> taxed;
            if (taxed != "Y" && taxed != "y" && taxed != "N" && taxed != "n") {
                std::cout << "Only 'y' and 'n' are acceptable";
            }
            else break;
        }

        m_taxed = taxed[0] == 'y' || taxed[0] == 'Y';

        int qty;
        std::cout << "Quantity\n";
        while (true) {
            std::cout << "> ";
            std::cin >> qty;
            if (std::cin.fail() || qty <= 0 || qty > MAX_STOCK_NUMBER) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << ERROR_POS_QTY << "\n";
            }
            else {
                std::cin.ignore(1000, '\n');
                break;
            }
        }
        m_qty = qty;

        return is;
    }

    std::ifstream& Item::load(std::ifstream& ifs) {
        m_err.clear();
        std::string SKU;
        std::getline(ifs, SKU, ',');
        if (SKU.length() > MAX_SKU_LEN || SKU.length() <= 0) {
            m_err = ERROR_POS_SKU;
            return ifs;
        }

        std::string name;
        std::getline(ifs, name, ',');
        if (name.length() > MAX_NAME_LEN || name.length() <= 0) {
            m_err = ERROR_POS_NAME;
            return ifs;
        }

        double price;
        ifs >> price;
        if (ifs.peek() == ',') ifs.ignore();
        if (price <= 0) {
            m_err = ERROR_POS_PRICE;
            return ifs;
        }
        bool isTaxed;
        ifs >> isTaxed;
        if (ifs.peek() == ',') ifs.ignore();

        int qty;
        ifs >> qty;
        if (qty < 0 || qty > MAX_STOCK_NUMBER) {
            m_err = ERROR_POS_QTY;
            return ifs;
        }

        if (!m_err) {
            delete[] m_SKU;
            m_SKU = new char[SKU.length() + 1];
            std::strcpy(m_SKU, SKU.c_str());

            delete[] m_name;
            m_name = new char[name.length() + 1];
            std::strcpy(m_name, name.c_str());

            m_price = price;
            m_taxed = isTaxed;
            m_qty = qty;
        }
        return ifs;
    }

    std::ostream& Item::bprint(std::ostream& os) const {
        if (m_err) {
            os << m_err;
            return os;
        }
        std::string name = m_name;
        os << "| " << std::setw(20) << std::left << name.substr(0, 20) << "|"
            << std::setw(10) << std::right << std::fixed << std::setprecision(2) << cost() << " |"
            << "  ";
        if (m_taxed) os << "T";
        else os << " ";
        os << "  |\n";
        return os;
    }

    double operator+=(double& num, const Item& item) {
        return num + (item.cost() * item.quantity());
    }

    const char* Item::getName() const {
        return m_name;
    }
    const char* Item::getSKU() const
    {
        return m_SKU;
    }
}
