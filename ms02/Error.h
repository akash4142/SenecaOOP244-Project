/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#define _CRT_SECURE_NO_WARNINGS
#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H
#include <cstring>
#include <iostream>

namespace sdds {
    class Error {
        char* message_;
    public:
        Error();
        Error(const char* errorMessage);
        Error(const Error& other);
        Error& operator=(const Error& other);
        ~Error();

        void message(const char* errorMessage);
        operator bool() const;
        Error& clear();
        const char* getMessage() const;
    };

    std::ostream& operator<<(std::ostream& os, const Error& error);
}
#endif 