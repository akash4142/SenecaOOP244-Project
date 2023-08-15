/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#ifndef SDDS_POSIO_H
#define SDDS_POSIO_H
#include <iostream>
namespace sdds
{
    class PosIO
    {
    public:
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;
        virtual std::ofstream& save(std::ofstream& ofs) const = 0;
        virtual std::ifstream& load(std::ifstream& ifs) = 0;
        virtual ~PosIO() = default;

        friend std::ostream& operator<<(std::ostream& os, const PosIO& obj);
        friend std::ofstream& operator<<(std::ofstream& ofs, const PosIO& obj);
        friend std::istream& operator>>(std::istream& is, PosIO& obj);
        friend std::ifstream& operator>>(std::ifstream& ifs, PosIO& obj);
    };

}

#endif