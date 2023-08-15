#define _CRT_SECURE_NO_WARNINGS
/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#include "PosApp.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Item.h"
#include <cstring>
#include <iomanip>
#include <fstream>
namespace sdds
{
    Bill PosApp::m_bill;
    PosApp::PosApp(const char* filename) {
        std::strcpy(m_filename, filename);
        loadRecs();
    }

    PosApp::~PosApp() {
        for (int i = 0; i < m_numItems; i++) {
            delete m_items[i];
        }
    }

    int PosApp::menu() {
        std::cout << "The Sene-Store\n";
        std::cout << "1- List items\n";
        std::cout << "2- Add item\n";
        std::cout << "3- Remove item\n";
        std::cout << "4- Stock item\n";
        std::cout << "5- POS\n";
        std::cout << "0- exit program\n";
        int choice;
        while (true) {
            std::cout << "> ";
        reentry:
            std::cin >> choice;
            if (std::cin.fail() || choice < 0 || choice > 5) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                if (choice > 5 || choice < 0) {
                    std::cout << "[0<=value<=5], retry: ";
                }
                else {
                    std::cout << "Invalid Integer, try again: ";
                    goto reentry;
                }
            }
            else {
                std::cin.ignore(1000, '\n');
                break;
            }
        }
        return choice;
    }

    void PosApp::addItem() {
        actionTitle("Adding Item to the store");
        if (m_numItems == MAX_NO_ITEMS) {
            std::cout << "Inventory Full!";
            return;
        }
        std::string isPerishable;
        std::cout << "Is the Item perishable? (Y)es/(N)o";
        while (true) {
            std::cout << ": ";
            std::cin >> isPerishable;
            if (isPerishable != "Y" && isPerishable != "y" && isPerishable != "N" && isPerishable != "n") {
                std::cout << "Only 'y' and 'n' are acceptable";
            }
            else break;
        }
        Item* item = nullptr;
        if (isPerishable[0] == 'Y' || isPerishable[0] == 'y') {
            item = new Perishable();
        }
        else {
            item = new NonPerishable();
        }

        while (true) {
            std::cin >> *item;
            if (*item) break;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << *item << ", try again...\n";
        }
        m_items[m_numItems++] = item;
        std::cout << ">>>> DONE!...................................................................\n";
    }

    void PosApp::removeItem() {
        actionTitle("Remove Item");
        int idx = selectItem();
        std::cout << "Removing....\n";
        std::cout << m_items[idx]->displayType(POS_FORM);
        delete m_items[idx];
        for (int i = idx; i < m_numItems; i++)
        {
            m_items[i] = m_items[i + 1];
        }
        m_numItems--;
        std::cout << ">>>> DONE!...................................................................\n";
    }

    void PosApp::stockItem() {
        actionTitle("Select an item to stock");
        int idx = selectItem();
        std::cout << "Selected Item:\n";
        std::cout << m_items[idx]->displayType(POS_FORM);
        int stock;
        std::cout << "Enter quantity to add: ";
        while (true) {
            std::cin >> stock;
            if (std::cin.fail() || stock < 1 || stock > MAX_STOCK_NUMBER - m_items[idx]->quantity()) {
                if ((!std::cin.fail()) && (stock < 1 || stock > MAX_STOCK_NUMBER - m_items[idx]->quantity())) {
                    std::cout << "[1<=value<=" << MAX_STOCK_NUMBER - m_items[idx]->quantity() << "], retry: Enter quantity to add: ";
                }
                else {
                    std::cout << "Invalid Integer, try again: ";
                }
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            else {
                std::cin.ignore(1000, '\n');
                break;
            }
        }
        *m_items[idx] += stock;
        std::cout << ">>>> DONE!...................................................................\n";
    }


    void PosApp::listItems()
    {
        actionTitle("Listing Items");
        sortItems();
        double totalAssets = 0;
        printHeader();
        for (int i = 0; i < m_numItems; i++)
        {
            std::cout << std::setw(4) << std::right << i + 1 << std::left << " | " << *m_items[i] << "\n";
            totalAssets += m_items[i]->cost() * m_items[i]->quantity();
        }
        std::cout << "-----^--------^--------------------^-------^---^----^---------^-------------^\n";
        std::cout << "                               Total Asset: $  |";
        std::cout << std::setw(14) << std::right << totalAssets << "|\n";
        std::cout << "-----------------------------------------------^--------------^\n\n";

    }

    void PosApp::POS() {
        actionTitle("Starting Point of Sale");
        while (true) {
            std::cout << "Enter SKU or <ENTER> only to end sale...\n";
            std::cout << "> ";
            char sku[8] = {};
            for (int i = 0; std::cin.good(); i++)
            {
                if (std::cin.peek() == '\n' && i >= 0 && i <= 7) break;
                else if (std::cin.peek() != '\n' && i >= 0 && i < 7)
                {
                    std::cin.get(sku[i]);
                }
                else {
                    std::cout << "SKU too long\n";
                    std::cout << "> ";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    i = -1;
                    memset(sku, 0, 8);
                }
            }

            std::cin.ignore();
            if (std::strlen(sku) == 0) break;

            Item* item = search(sku);
            if (item == nullptr) {
                std::cout << "!!!!! Item Not Found !!!!!\n";
            }
            else {
                *item -= 1;
                std::cout << item->displayType(POS_FORM) << "\n";
                if (*item) {
                    m_bill.add(item);
                    std::cout << ">>>>> Added to bill\n";
                    std::cout << ">>>>> Total: " << m_bill.total() << "\n";
                }
                else {
                    item->clear();
                }
            }
        }
        m_bill.print(std::cout);
    }

    void PosApp::loadRecs() {
        actionTitle("Loading Items");
        std::ifstream temp(m_filename);
        if (!temp) {
            temp.close();
            std::ofstream f(m_filename);
            f.close();
        }
        temp.close();
        std::ifstream file(m_filename);
        clear();
        while (file.peek() != EOF && m_numItems < MAX_NO_ITEMS) {
            char itemType;
            file.get(itemType);

            if (itemType == 'P') {
                m_items[m_numItems] = new Perishable();
            }
            else {
                m_items[m_numItems] = new NonPerishable();
            }

            file.ignore();
            file >> *m_items[m_numItems];
            file.ignore();
            m_numItems += 1;
        }

    }
    void PosApp::saveRecs() {
        actionTitle("Saving Data");
        std::ofstream file(m_filename);
        for (int i = 0; i < m_numItems; i++)
        {
            file << *m_items[i] << "\n";
        }
    }
    int PosApp::selectItem()
    {
        actionTitle("Item Selection by row number");
        std::cout << "Press <ENTER> to start....";
        std::cin.get();
        actionTitle("Listing Items");
        sortItems();
        printHeader();
        for (int i = 0; i < m_numItems; i++)
        {
            std::cout << std::setw(4) << std::right << i + 1 << " | " << *m_items[i] << "\n";
        }
        std::cout << "-----^--------^--------------------^-------^---^----^---------^-------------^\n";

        int choice;
        std::cout << "Enter the row number: ";
        while (true) {
            std::cin >> choice;            if (std::cin.fail() || choice < 1 || choice > m_numItems) {
                if ((!std::cin.fail()) && (choice < 1 || choice > m_numItems)) {
                    std::cout << "[1<=value<=" << m_numItems << "], retry: Enter the row number: ";
                }
                else {
                    std::cout << "Invalid Integer, try again: ";
                }
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            else {
                std::cin.ignore(1000, '\n');
                break;
            }
        }

        return --choice;
    }


    void PosApp::run() {
        int choice;
        while (true) {

            choice = menu();
            if (choice == 0) {
                saveRecs();
                std::cout << "Goodbye!\n";
                break;
            }
            else if (choice == 1) {
                listItems();
            }
            else if (choice == 2) {
                addItem();
            }
            else if (choice == 3) {
                removeItem();
            }
            else if (choice == 4) {
                stockItem();
            }
            else if (choice == 5) {
                POS();
            }
        }
    }
    void PosApp::actionTitle(std::string title)const {
        std::cout << ">>>> " << std::setw(72) << std::setfill('.') << std::left << title << "\n";
        std::cout << std::setfill(' ');
    }

    void PosApp::clear() {
        for (int i = 0; i < MAX_NO_ITEMS; i++) {
            delete m_items[i];
            m_items[i] = nullptr;
        }
        m_numItems = 0;
    }

    void PosApp::printHeader() {
        std::cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |\n";
        std::cout << "-----|--------|--------------------|-------|---|----|---------|-------------|\n";
    }

    void PosApp::sortItems()
    {
        for (int i = 0; i < m_numItems; i++)
        {
            for (int j = i + 1; j < m_numItems; j++)
            {
                if (std::strcmp(m_items[i]->getName(), m_items[j]->getName()) > 0)
                {
                    Item* temp = m_items[i];
                    m_items[i] = m_items[j];
                    m_items[j] = temp;
                }
            }
        }
    }

    Item* PosApp::search(const char* sku) {
        for (int i = 0; i < m_numItems; i++)
        {
            if (std::strcmp(m_items[i]->getSKU(), sku) == 0)
            {
                return m_items[i];
            }
        }
        return nullptr;
    }

}

