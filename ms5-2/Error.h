/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H
#include <iostream>
namespace sdds
{
    class Error
    {
    private:
        char* m_errormsg = nullptr;
    public:
        Error() {};
        Error(const char* err);
        Error(const Error& temp);
        Error& operator= (const Error& temp);
        Error& operator= (const char* err);
        Error& operator= (const std::string& err);
        operator bool() const;
        Error& clear();
        ~Error();


        char* message() const;
    };

    std::ostream& operator<< (std::ostream& os, const Error& err);
}

#endif