#define _CRT_SECURE_NO_WARNINGS
/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/

#include <algorithm>
#include <iostream>
#include <cstring>
#include "PosApp.h"
#include <fstream>
#include <iomanip>
#include "NonPerishable.h"
#include "Perishable.h"

using namespace std;
namespace sdds {

    PosApp::PosApp(const char* filename) {
        strncpy(f_filename, filename, 128);
        f_filename[128] = '\0';
        m_nptr = 0;
        for (int i = 0; i < MAX_NO_ITEMS; i++) {
            m_Iptr[i] = nullptr;
        }
    }
	PosApp::~PosApp() {
        for (int i = 0; i < MAX_NO_ITEMS; i++) {
            delete m_Iptr[i];
            m_Iptr[i] = nullptr;
        }
    }
    int PosApp::menu() {
        int choice = -1;
        cout << "The Sene-Store" << endl;
        cout << "1- List items" << endl;
        cout << "2- Add item" << endl;
        cout << "3- Remove item" << endl;
        cout << "4- Stock item" << endl;
        cout << "5- POS" << endl;
        cout << "0- exit program" << endl;
        cout << ">";
        while (choice < 0 || choice > 5) {
            cout << " ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Integer, try again:";
                choice = -1;
            }
            else if (choice < 0 || choice > 5) {
                cout << "[0<=value<=5], retry: >";
            }
        }

        return choice;
    }
    void PosApp::run() {
        int choice = -1;
        loadRecs();
        while (choice != 0) {

            choice = menu();
            switch (choice) {
            case 0:
                saveRecs();
                cout << "Goodbye!" << endl;
                break;
            case 1:
                listItems();
                break;
            case 2:

                addItem();
                break;
            case 3:
                removeItem();
                break;
            case 4:
                stockItem();
                break;
            case 5:
                POS();
                break;
            default:
                std::cout << "Invalid choice, try again:";
                break;
            }
        }
    }
    void PosApp::addItem() {

    
    }

    void PosApp::listItems() {
        cout << ">>>> Listing Items..........................................................." << endl;

        // Sort the items in the Iptr array by name
        sort(m_Iptr, m_Iptr + m_nptr, [](Item* a, Item* b) {return strcmp(a->name(), b->name()) < 0; });

        // Print the header of the list
        cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << endl;
        cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;

        double totalAsset = 0.0;

        // Loop through the items and print them in POS_LIST format
        for (int i = 0; i < m_nptr; i++) {

            cout << setw(4) << right << i + 1 << " | ";
            cout << m_Iptr[i]->displayType(POS_LIST) << endl;
            totalAsset += m_Iptr[i]->cost() * m_Iptr[i]->quantity();
        }

        // Print the footer and the total asset
        cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
        cout << "                               Total Asset: $  |" << setw(14) << right << fixed << setprecision(2) << totalAsset << "|" << endl;
        cout << "-----------------------------------------------^--------------^\n" << endl;
    }


    void PosApp::loadRecs() {
        cout << ">>>> Loading Items..........................................................." << endl;

        // Open the data file for reading
        ifstream input(f_filename);
        // If opening the file was not successful create the file
        if (input.fail()) {
            ofstream file(f_filename);
            file.close();
            return;
        }

        // Empty the PosApp class
        for (int i = 0; i < MAX_NO_ITEMS; i++) {
    if (m_Iptr[i] != nullptr) {
        delete m_Iptr[i];
        m_Iptr[i] = nullptr;
    }
}
        m_nptr = 0;

        // Read each record from the input file and add it to the Item array
        char recordType;
        while (input >> recordType && m_nptr < MAX_NO_ITEMS) {
            delete m_Iptr[m_nptr];
    m_Iptr[m_nptr] = nullptr;
            if (recordType == 'N') {
                m_Iptr[m_nptr] = new NonPerishable;
            }
            else if (recordType == 'P') {           
                m_Iptr[m_nptr] = new Perishable;
            }
            if (m_Iptr[m_nptr] != nullptr) {
                input.ignore();
                m_Iptr[m_nptr]->load(input);
                m_nptr++;
            }

        }
	// Delete any remaining items in the PosApp class
    for (int i = m_nptr; i < MAX_NO_ITEMS; i++) {
        delete m_Iptr[i];
        m_Iptr[i] = nullptr;
    }		
    }

    void PosApp::saveRecs() {
        cout << ">>>> Saving Data............................................................." << endl;
        ofstream file(f_filename);
        if (file.is_open()) {
            for (int i = 0; i < m_nptr; i++) {
                m_Iptr[i]->save(file) << endl;
            }
            file.close();
        }
        else {
            cout << "Could not open data file: " << f_filename << endl;
        }
    }


    void PosApp::removeItem() {
        cout << ">>>> Remove Item............................................................." << endl;
    }
    void PosApp::stockItem() {
        cout << ">>>> Select an item to stock................................................." << endl;
    }

    void PosApp::POS() {
        cout << ">>>> Starting Point of Sale.................................................." << endl;
    }


};