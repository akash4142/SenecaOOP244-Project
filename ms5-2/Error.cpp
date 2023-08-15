#define _CRT_SECURE_NO_WARNINGS
/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include "Error.h"
#include <cstring>
namespace sdds
{
    Error::Error(const char* err) {
        if (err != nullptr && err[0] != '\0') {
            m_errormsg = new char[std::strlen(err) + 1];
            std::strncpy(m_errormsg, err, std::strlen(err) + 1);
        }
    }

    Error::Error(const Error& temp) {
        *this = temp;
    }

    Error& Error::operator= (const Error& temp) {
        delete[] m_errormsg;
        m_errormsg = nullptr;

        if (temp.m_errormsg != nullptr) {
            m_errormsg = new char[std::strlen(temp.m_errormsg) + 1];
            std::strncpy(m_errormsg, temp.m_errormsg, std::strlen(temp.m_errormsg) + 1);
        }
        return *this;
    }

    Error& Error::operator= (const char* err) {
        delete[] m_errormsg;
        m_errormsg = nullptr;

        if (err != nullptr) {
            m_errormsg = new char[std::strlen(err) + 1];
            std::strncpy(m_errormsg, err, std::strlen(err) + 1);
        }
        return *this;
    }

    Error& Error::operator= (const std::string& err) {
        delete[] m_errormsg;
        m_errormsg = nullptr;

        if (err.length() > 0) {
            m_errormsg = new char[err.length() + 1];
            std::strncpy(m_errormsg, err.c_str(), err.length() + 1);
        }
        return *this;
    }

    Error::operator bool() const {
        return m_errormsg != nullptr;
    }

    Error& Error::clear() {
        delete[] m_errormsg;
        m_errormsg = nullptr;

        return *this;
    }

    Error::~Error() {
        delete[] m_errormsg;
    };

    std::ostream& operator<< (std::ostream& os, const Error& err) {
        if (err) {
            os << err.message();
        }
        return os;
    }


    char* Error::message() const {
        return m_errormsg;
    }
}
