/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-: 

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#define _CRT_SECURE_NO_WARNINGS
#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H
#define MAX_CHAR 255

namespace sdds {

	class PosApp{
		char filename[MAX_CHAR + 1];

	public:
		PosApp();
		PosApp(const char* filename);
		PosApp(const PosApp& right);
		PosApp& operator=(const PosApp& right) ;

		void isempty();
		int menu();
		void addItem();
		void removeItem();
		void stockItem();
		void listItems();
		void POS();
		void saveRecs();
		void loadRecs();
		void run();
	
	
	};


}

#endif 