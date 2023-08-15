/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-: 

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "PosApp.h"
#include "cstring"

using namespace std;
namespace sdds {

	PosApp::PosApp() {
		isempty();
	}

	PosApp::PosApp(const char* filename) {
		if (filename != nullptr && filename[0] != '\0') {
			strcpy(this->filename, filename);
			this->filename[255] = '\0';
		}
		else {
			isempty();
		}
	}

	PosApp::PosApp(const PosApp& right) {
		if (right.filename != nullptr && right.filename[0] != '\0') {
			strcpy(filename, right.filename);
			filename[255] = '\0';
		}
		else {
			isempty();
		}
	};
	
	PosApp& PosApp::operator=(const PosApp& right) {
		if (this != &right) {
			if (right.filename != nullptr && right.filename[0] != '\0') {
				strcpy(filename, right.filename);
				filename[255] = '\0';
			}
		}
		else {
			isempty();
		}
		return *this;
	};

	int PosApp::menu() {
		int choice = -1;
		
			cout << "The Sene-Store" << endl;
			cout << "1- List items" << endl;
			cout << "2- Add item" << endl;
			cout << "3- Remove item" << endl;
			cout << "4- Stock item" << endl;
			cout << "5- Point of Sale" << endl;
			cout << "0- exit program" << endl;
cout<<"> ";
			cin >>choice;
			do {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				choice = -1;
				cout << "Invalid Integer, try again: ";
				cin >> choice;
			}
			if (choice < 0 || choice >5) {
				cout << "[0<=value<=5], retry: > ";
			    cin >> choice;
				}
			} while (choice <0 || choice > 5);
			
		return choice;
	}

	void PosApp::isempty() {
		filename[0] = '\0';
	}


	void PosApp::addItem() {
cout<<">>>> Adding Item to the store................................................"<<endl;
		cout << "Running addItem()" << endl;
	}

	void PosApp::removeItem() {
cout<<">>>> Remove Item............................................................."<<endl;
		cout << "Running removeItem()" << endl;
	}

	void PosApp::stockItem() {
cout<<">>>> Select an item to stock................................................."<<endl;
		cout << "Running stockItem()" << endl;
	}

	void PosApp::listItems() {
cout<<">>>> Listing Items..........................................................."<<endl;
		cout << "Running listItems()" << endl;
	}

	void PosApp::POS() {
cout<<">>>> Starting Point of Sale.................................................."<<endl;
		cout << "Running POS()" << endl;
	}

	void PosApp::saveRecs() {
cout<<">>>> Saving Data............................................................."<<endl;
		cout << "Saving data in datafile.csv" << endl;
	}

	void PosApp::loadRecs() {
cout<<">>>> Loading Items..........................................................."<< endl;
cout<<"Loading data from datafile.csv"<<endl;
	}

	void PosApp::run() {
		loadRecs();
		bool flag = false;
		int choice =-1;
		do {
			choice = menu();
			switch (choice) {
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
			case 0:
saveRecs();
				cout << "Goodbye!" << endl;
				flag = true;
				break;
			}
		} while (!flag);
		
	}
}