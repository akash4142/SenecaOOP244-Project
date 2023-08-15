/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H
#include "Item.h"
#include "POS.h"
#include "Bill.h"
#include <iostream>
#include <fstream>
#include <string>
namespace sdds
{
    class PosApp
    {
    private:

        char m_filename[128];
        Item* m_items[MAX_NO_ITEMS] = { nullptr };
        int m_numItems = 0;
        static Bill m_bill;
        void clear();
        void printHeader();
        void sortItems();
        Item* search(const char* sku);
    public:
        PosApp(const char* filename);
        ~PosApp();
        int menu();
        int selectItem();
        void addItem();
        void removeItem();
        void stockItem();
        void listItems();
        void POS();
        void loadRecs();
        void saveRecs();
        void run();
        void actionTitle(std::string title)const;
    };

}

#endif