/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/

#ifndef SDDS_ITEM_H_
#define SDDS_ITEM_H_
#include <iostream>
#include "POS.h"
#include "Error.h"
#include "PosIO.h"

using namespace std;
namespace sdds
{
	class Item: public PosIO
	{
		char sku[MAX_SKU_LEN+1]{};
		char* itemName;
		double price;
		bool tax;
		int numberOfItem;

		void setEmpty();
		void setError(const char* errorMessage);

		protected:
			int dplayType;
			Error error;

		public:
			Item();
			Item(const Item& other);
			Item& operator = (const Item& other);
			bool operator==(const char* right) const;
			bool operator>(const Item& right) const;
			int operator+=(int quantity);
			int operator-=(int quantity);
			operator bool() const;

			virtual char itemType()const = 0;
			Item& displayType(int dType);
			double getPrice() const;
			double cost() const;
			int quantity() const;
			
			Item& clear();
			ostream& write(ostream& ostr) const override;
			istream& read(istream& istr) override;
			ofstream& save(ofstream& ostr)const override;
			ifstream& load(ifstream& istr) override;

			ostream& bprint(ostream& ostr);
			~Item();
	};

	double& operator+=(double& otherItem, const Item& item);
}

#endif // !SDDS_ITEM_H_
