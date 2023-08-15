/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>
#include "Utils.h"
#include "Error.h"
#include "Item.h"

using namespace std;

namespace sdds
{
	// default constructor
	Item::Item()
	{
		setEmpty();
	}

	// Copy constructor
	Item::Item(const Item& other)
	{
		clear();

		strcpy(sku, other.sku);
		if (other.itemName != nullptr && other.itemName[0] != '\0')
		{
			if (itemName != nullptr && itemName[0] != '\0')
			{
				delete[] itemName;
				itemName = nullptr;
			}
			itemName = new char[strlen(other.itemName) + 1];
			strcpy(itemName, other.itemName);
		}
		else
		{
			itemName = nullptr;
		}

		price = other.price;
		tax = other.tax;
		numberOfItem = other.numberOfItem;
		dplayType = other.dplayType;
		error = other.error;
	}



	// Copy assignment operator
	Item& Item::operator = (const Item& other)
	{
		if (this != &other)   // check for self-assignment
		{
			clear();

			strcpy(sku, other.sku);

			delete[] itemName;
			itemName = nullptr;

			if (other.itemName!=nullptr && other.itemName[0]!='\0')
			{
				// Free any memory allocated to the current object
				//if (itemName != nullptr && itemName[0] != '\0')
				//{
					//delete[] itemName;
					//itemName = nullptr;
				//}

				itemName = new char[strlen(other.itemName) + 1];
				strcpy(itemName, other.itemName);
			}
			else
			{
				itemName = nullptr;
			}
			price = other.price;
			tax = other.tax;
			numberOfItem = other.numberOfItem;
			dplayType = other.dplayType;
			error = other.error;
		}
		return *this; // return a reference to the current object
	}

	void Item::setEmpty()
	{
		sku[0] = '\0';

		//if (itemName != nullptr) delete[] itemName;
		itemName = nullptr;

		price = 0.0;
		tax = false;
		numberOfItem = 0;
		dplayType = 0;
		error.clear();
	}

	void Item::setError(const char* errorMessage)
	{
		Error err(errorMessage);
		error = err;
	}

	bool Item::operator == (const char* right) const
	{
		return strcmp(sku, right) == 0;
	}

	bool Item::operator>(const Item& right) const
	{
		return strcmp(itemName, right.itemName) >= 0;
	}

	int Item::operator+=(int quantity)
	{
		numberOfItem += quantity;
		if (numberOfItem > MAX_STOCK_NUMBER)
		{
			numberOfItem = MAX_STOCK_NUMBER;
			setError(ERROR_POS_QTY);
		}
		return numberOfItem;
	}

	int Item::operator-=(int quantity)
	{
		numberOfItem -= quantity;
		if (numberOfItem < 0)
		{
			numberOfItem = 0;
			
			setError(ERROR_POS_STOCK);
		}
		return numberOfItem;
	}

	Item::operator bool() const
	{
		return !error;
	}

	Item& Item::displayType(int dType)
	{
		if (dType == POS_FORM || dType == POS_LIST)
		{
			dplayType = dType;
		}
		return *this;
	}

	double Item::getPrice() const
	{
		return price;
	}

	double Item::cost() const
	{
		return (tax) ? price * (1.0 + TAX_RATE) : price;
	}

	int Item::quantity() const
	{
		return numberOfItem;
	}

	Item& Item::clear()
	{
		error.clear();
		return *this;
	}

	ostream& Item::write(ostream& ostr) const
	{
		if (error)
		{
			ostr << error;
		}
		else
		{
			if (dplayType == POS_LIST)
			{
				string str20(itemName);
				ostr << setw(MAX_SKU_LEN) << left << sku << '|'
					<< setw(20) << left << str20.substr(0,20) << '|'
					<< setw(7) << right << fixed << setprecision(2) << getPrice() << '|'
					<< ' ' << (tax ? 'X' : ' ') << " |"
					<< setw(4) << right << quantity() << '|'
					<< setw(9) << right << fixed << setprecision(2) << (cost()*quantity()) << '|';
			}
			else if (dplayType == POS_FORM)
			{
				ostr << "=============v"<<endl;
				ostr << setw(13) << left << setfill(' ') << "Name:";
				ostr << itemName << endl;
				ostr << setw(13) << left << setfill(' ') << "Sku:";
				ostr << sku << endl;
				ostr << setw(13) << left << setfill(' ') << "Price:";
				ostr << fixed << setprecision(2) << getPrice() << endl;
				if (tax)
				{
					ostr << setw(13) << left << setfill(' ') << "Price + tax:";
					ostr << fixed << setprecision(2) << cost() << endl;
				}
				else
				{
					ostr << "Price + tax: N/A" << endl;
				}
				ostr << setw(13) << left << setfill(' ') << "Stock Qty:";
				ostr << quantity() << endl;
			}
		}

		return ostr;
	}

	ofstream& Item::save(ofstream& ostr)const
	{
		if (!error)
		{
			ostr << itemType() << ','
				<< sku << ','
				<< itemName << ','
				<< fixed << setprecision(2)<<getPrice() << ','
				<< (tax?1:0) << ','
				<< quantity();
		}
		else
		{
			cerr << error;
		}
		return ostr;
	}

	istream& Item::read(istream& istr)
	{
		string localItemName;
		char taxedInput;
		bool requireInput = true;

		clear();

		cout << "Sku"<<endl;
		while (requireInput)
		{
			cout << "> ";
			istr >> sku;
			requireInput = false;
			if (strlen(sku)> MAX_SKU_LEN || istr.fail())
			{
				requireInput = true;
				cout << ERROR_POS_SKU << endl;
				istr.clear();
				istr.ignore(1000,'\n');
			}
		}

		requireInput = true;
		istr.ignore();
		cout << "Name"<<endl;
		while (requireInput)
		{
			cout << "> ";
			getline(istr, localItemName);
			requireInput = false;
			if (localItemName.size() > MAX_NAME_LEN || istr.fail())
			{
				requireInput = true;
				cout << ERROR_POS_NAME << endl;
				if (istr.fail())
				{
					istr.clear();
					istr.ignore(1000, '\n');
				}

			}
			else
			{
				// Free any memory allocated to the current object
				if (itemName != nullptr && itemName[0] != '\0')
				{
					delete[] itemName;
					itemName = nullptr;
				}

				itemName = new char[localItemName.size() + 1];
				strcpy(itemName, localItemName.c_str());
			}
		}

		requireInput = true;
		cout << "Price" << endl;
		while (requireInput)
		{
			cout << "> ";
			istr >> price;
			requireInput = false;
			if (istr.fail() || price <= 0)
			{
				requireInput = true;
				cout << "Invalid price value" << endl;
				istr.clear();
				istr.ignore(1000, '\n');
			}
		}

		requireInput = true;
		istr.ignore();
		cout << "Taxed?" << endl;
		cout << "(Y)es/(N)o: ";
		while (requireInput)
		{		
			istr >> taxedInput;
			requireInput = false;
			if (taxedInput =='Y' || taxedInput == 'y')
			{
				tax = 1;
			}
			else if (taxedInput == 'N' || taxedInput == 'n')
			{
				tax = 0;
			}
			else if(istr.fail())
			{

				requireInput = true;
				cout << ERROR_POS_TAX << endl;
				istr.clear();
				istr.ignore(1000, '\n');
			}
			else
			{
				requireInput = true;
				cout << "Only 'y' and 'n' are acceptable: ";
				istr.ignore(1000, '\n');
			}
		}

		requireInput = true;
		istr.ignore();
		cout << "Quantity" << endl;
		while (requireInput)
		{
			cout << "> ";
			istr >> numberOfItem;
			requireInput = false;
			if (numberOfItem<=0 || numberOfItem> MAX_STOCK_NUMBER || istr.fail())
			{
				requireInput = true;
				cout << ERROR_POS_QTY << endl;
				istr.clear();
				istr.ignore(1000, '\n');
			}
		}

		return istr;
	}

	ifstream& Item::load(ifstream& ifstr)
	{
		
		// read values from file
		char delim = ',';
		string localSku;
		string localItemName;
		double localPrice;
		bool localTax;
		int localNumBerOfItems;
		string errorMsg;

		getline(ifstr, localSku, delim);
		getline(ifstr, localItemName, delim);

		ifstr >> localPrice;
		ifstr.ignore();

		ifstr >> localTax;
		ifstr.ignore();

		ifstr >> localNumBerOfItems;

		// check for errors during reading
		if (ifstr.fail())
		{
			setError("Unable to read data from file");
		}else{

			if (localSku.size() > MAX_SKU_LEN)
			{
				errorMsg = ERROR_POS_SKU;
			}

			if (errorMsg.empty() && localItemName.size() > MAX_NAME_LEN)
			{
				errorMsg = ERROR_POS_NAME;
			}			
			
			if (errorMsg.empty() && localPrice<=0)
			{
				errorMsg = "Invalid price value";
			}

			if (errorMsg.empty() && localTax!=0 && localTax!=1)
			{
				errorMsg = ERROR_POS_TAX;
			}

			if (errorMsg.empty() &&  (localNumBerOfItems <= 0 || localNumBerOfItems > MAX_STOCK_NUMBER ))
			{
				errorMsg =  ERROR_POS_QTY;
			}

			if(errorMsg.empty())
			{

				clear();

				// set values to attributes			
				strcpy(sku, localSku.c_str());

				// Free any memory allocated to the current object
				if (itemName != nullptr)
				{
					delete[] itemName;
					itemName = nullptr;
				}

				itemName = new char[localItemName.size() + 1];
				strcpy(itemName, localItemName.c_str());
				price = localPrice;
				tax = localTax;
				numberOfItem = localNumBerOfItems;
			}
			else
			{
				setError(errorMsg.c_str());
			}
		}

		return ifstr;
	}

	ostream& Item::bprint(ostream& ostr)
	{
		string str(itemName);

		// Print the name, truncated to 20 characters if necessary
		ostr << "| ";
		ostr << left << setw(20) << setfill(' ') << str.substr(0,20);

		// Print the price, including tax if the item is taxable
		ostr << "|";
		if (tax)
		{
			ostr << setw(10) << right << fixed << setprecision(2) << cost();
			ostr << " |  T  |";
		}
		else
		{
			ostr << setw(10) << right << fixed << setprecision(2) << price;
			ostr << " |     |";
		}
		ostr << endl;

		// Return the ostream reference
		return ostr;
	}

	// Destructor
	Item::~Item()
	{


		delete[] itemName;
		itemName = nullptr;

		clear();

	}

	double& operator+=(double& otherItem, const Item& item)
	{
		otherItem += item.cost() * item.quantity();
		return otherItem;
	}
}