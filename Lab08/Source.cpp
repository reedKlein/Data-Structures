#include "Header.h"
#include <string>
#include <iostream>
using namespace std;

int main() {
	LinkedList newList;
	Part retrieved_part;
	bool userContinue = true;
	int userChoice;
	string userContinuePrompt;
	string userWantToInputQuantity;
	string inputSKU;
	string inputDescription;
	string inputUOM;
	int inputPrice;
	int inputQuantity;
	int inputIndex;
	while (userContinue) {
		cout << "Enter 1 to add a new part" << endl;
		cout << "Enter 2 to get a part" << endl;
		cout << "Enter 3 to see if an item is in the list" << endl;
		cout << "Enter 4 to see if the list is empty" << endl;
		cout << "Enter 5 to see the size of the list" << endl;
		cout << "Enter 6 to see the next item in the list" << endl;
		cout << "Enter 7 to see the previous item in the list" << endl;
		cout << "Enter 8 to see the item at a particular position in the list" << endl;
		cout << "Enter 9 to reset the see position" << endl;
		cin >> userChoice;
		if (userChoice == 1) {
			cout << "Enter the SKU: " << endl;
			cin >> inputSKU;
			cout << "Enter the description: " << endl;
			cin >> inputDescription;
			cout << "Enter the price: " << endl;
			cin >> inputPrice;
			cout << "Enter the unit of measure: " << endl;
			cin >> inputUOM;
			cout << "Do you wish to input the quantity on hand? (Y/N)" << endl;
			cin >> userWantToInputQuantity;
			if (userWantToInputQuantity == "Y")
			{
				cout << "Enter the quantity on hand: " << endl;
				cin >> inputQuantity;
				Part* newPart = new Part(inputSKU, inputDescription, inputPrice, inputUOM, inputQuantity);
				newList.AddItem(*newPart);
			}
			else {
				Part* newPart = new Part(inputSKU, inputDescription, inputPrice, inputUOM);
				newList.AddItem(*newPart);
			}
		}
		else if (userChoice == 2) {
			cout << "Enter SKU of item you would like to get: " << endl;
			cin >> inputSKU;
			retrieved_part = newList.GetItem(inputSKU)->part;
			cout << "Item retrieved: " << retrieved_part.GetPartInfo() << endl;
		}
		else if (userChoice == 3) {
			cout << "Enter the SKU of item you would like to search for: " << endl;
			cin >> inputSKU;
			if (newList.IsInList(inputSKU))
			{
				cout << "Item is in list." << endl;
			}
			else
			{
				cout << "Item is not in list." << endl;
			}
		}
		else if (userChoice == 4) {
			if (newList.IsEmpty())
			{
				cout << "List is empty." << endl;
			}
			else
			{
				cout << "List is not empty." << endl;
			}
		}
		else if (userChoice == 5) {
			cout << "Size of list is: " << newList.Size() << endl;
		}
		else if (userChoice == 6) {
			retrieved_part = newList.SeeNext()->part;
			cout << "Item seen: " << retrieved_part.GetPartInfo() << endl;
		}
		else if (userChoice == 7) {
			retrieved_part = newList.SeePrev()->part;
			cout << "Item seen: " << retrieved_part.GetPartInfo() << endl;
		}
		else if (userChoice == 8) {
			cout << "Enter the position of item you would like to view: " << endl;
			cin >> inputIndex;
			retrieved_part = newList.SeeAt(inputIndex)->part;
			cout << "Item seen: " << retrieved_part.GetPartInfo() << endl;
		}
		else if (userChoice == 9) {
			newList.Reset();
			cout << "List reset." << endl;
		}
		newList.Print();
		cout << endl;
		cout << "Would you like to continue? Y/N " << endl;
		cin >> userContinuePrompt;
		if (userContinuePrompt == "N")
		{
			userContinue = false;
		}
	
	}

	return 0;
}