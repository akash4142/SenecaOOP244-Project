/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include "Perishable.h"
namespace sdds
{
    char Perishable::itemType() const
    {
        return 'P';
    }
    std::istream& Perishable::read(std::istream& is)
    {
        Item::read(is);
        if (*this && is.good())
        {
            Date expirydate;
            std::cout << "Expiry date (YYYY/MM/DD)\n"
                << "> ";
            is >> expirydate;
            if (!expirydate.error())
            {
                m_expirydate = expirydate;
            }
            else
            {
                m_err = expirydate.error();
            }
            return is;
        }
        else
        {
            return is;
        }
    }
    std::ostream& Perishable::write(std::ostream& os) const
    {
        Item::write(os);
        if (!*this)
        {
            return os;
        }
        if (m_displayType == POS_LIST)
        {
            os << "  " << m_expirydate << " "
                << "|";
        }
        if (m_displayType == POS_FORM)
        {
            os << "Expiry date: " << m_expirydate << "\n"
                << "=============^\n";

        }
        return os;
    }
    std::ifstream& Perishable::load(std::ifstream& ifs)
    {
        Item::load(ifs);
        if (*this && ifs.good())
        {
            Date expirydate;
            expirydate.dateOnly(true);
            ifs.ignore();
            ifs >> expirydate;
            if (!expirydate.error())
            {
                m_expirydate = expirydate;
            }
            else
            {
                m_err = expirydate.error();
            }
            return ifs;
        }
        else
        {
            return ifs;
        }
    }
    std::ofstream& Perishable::save(std::ofstream& ofs) const
    {
        Item::save(ofs);
        if (*this)
        {
            ofs << "," << m_expirydate;
            return ofs;
        }
        else
        {
            return ofs;
        }
    }
}