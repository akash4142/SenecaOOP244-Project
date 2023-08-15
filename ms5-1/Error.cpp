#define _CRT_SECURE_NO_WARNINGS
/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include <cstring>
#include <iostream>
#include "Error.h"

namespace sdds {

    Error::Error() {
        m_error = nullptr;
    }

    Error::Error(const char* error) : Error() {
        if (!error) return;
        int len = strlen(error);
        m_error = new char[len + 1]; 
        strcpy(m_error, error);
    }

    Error::Error(const Error& other) : Error(other.m_error) {
    }

    Error::~Error() {
        clear();
    }

    Error& Error::operator=(const Error& other) {
        clear();
        if (other.m_error) {
            int len = strlen(other.m_error);
            m_error = new char[len + 1]; 
            strcpy(m_error, other.m_error);
        }
        return *this;
    }

    Error::operator bool() const {
        if (m_error)
            return true;
        return false;
    }

    Error& Error::clear() {
        if (m_error)
            delete[] m_error;

        m_error = nullptr;
        return *this;
    }

    void Error::display(ostream& out) const {
        if (*this)
            out << m_error;
    }

    ostream& operator<<(ostream& out, const Error& err) {
        err.display(out);
        return out;
    }

}