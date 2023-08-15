/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/

#ifndef SDDS_PosApp_H_
#define SDDS_PosAPP_H_
#include "Item.h"
namespace sdds {
	class PosApp {
		char f_filename[128];
	public:
		
		Item* m_Iptr[MAX_NO_ITEMS] = {0};
		int m_nptr = 0;
		PosApp(const char* filename);
		PosApp(const PosApp&) = delete;
		~PosApp();
		PosApp& operator=(const PosApp&) = delete;
		int menu();
		void addItem();
		void removeItem();
		void stockItem();
		void listItems();
		void saveRecs();
		void loadRecs();
		void run();
		void POS();
	};
}
#endif