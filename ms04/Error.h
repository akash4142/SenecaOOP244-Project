/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#ifndef SDDS_ERROR_H_
#define SDDS_ERROR_H_
#include <iostream>

namespace sdds {
    class Error {
    public:
        Error();
        Error(const char* error);
        Error(const Error& other);
        ~Error();
        Error& operator=(const Error& other);
        operator bool() const;
        Error& clear();
        void display(std::ostream& out) const;

    private:
        char* m_error;
    };
    std::ostream& operator<<(std::ostream& out, const Error& err);
}
#endif 