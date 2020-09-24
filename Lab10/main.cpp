#include <string>
#include <iostream>

#include "HashTable.h"
#include "ChainedHashTable.h"
#include "Part.h"

using namespace std;

//-------------------------------------------------------------------//
// Lab10 Solution: Basketbal 4: Electric Boogcunttoo                 //
// Authors: Liam Sheerajin, Reed Klein, Dominic Boyte, Alex Davison  //
// Lab Period: Section 002 | Monday 2:30 PM - 5:30 PM                //
// Group Number: 13                                                  //
// This progam does stuff and it works well.                         //
//-------------------------------------------------------------------//

int main() {
	//// Hash table -------------------------------------------------------//
	//	// Initialize variables
	//HashTable<Part> PartTable;
	//ChainedHashTable<Part> ChainedPartTable;
	//Part* retrieved_part = new Part;
	//bool userContinue = true;
	//int userChoice;
	//string userContinuePrompt;
	//string userWantToInputQuantity;
	//string inputSKU;
	//string inputDescription;
	//string inputUOM;
	//int inputPrice;
	//int inputQuantity;
	//int inputIndex;

	//// Prompt user
	//cout << "Would you like to use a:" << endl;
	//cout << "1) Hash Table" << endl;
	//cout << "2) Chained Hash Table" << endl;
	//cin >> userChoice;

	//// 1) Hash Table
	//if (userChoice == 1) {
	//	// Program Loop
	//	while (userContinue) {
	//		cout << "Enter 1 to add a new part" << endl;
	//		cout << "Enter 2 to remove a part" << endl;
	//		cout << "Enter 3 to get a part" << endl;
	//		cout << "Enter 4 to get the length" << endl;
	//		cin >> userChoice;

	//		// Add new part
	//		if (userChoice == 1) {
	//			cout << "Enter the SKU: " << endl;
	//			cin >> inputSKU;
	//			cout << "Enter the description: " << endl;
	//			cin >> inputDescription;
	//			cout << "Enter the price: " << endl;
	//			cin >> inputPrice;
	//			cout << "Enter the unit of measure: " << endl;
	//			cin >> inputUOM;
	//			cout << "Do you wish to input the quantity on hand? (y/n)" << endl;
	//			cin >> userWantToInputQuantity;
	//			if (userWantToInputQuantity == "y")
	//			{
	//				cout << "Enter the quantity on hand: " << endl;
	//				cin >> inputQuantity;
	//				Part* newPart = new Part(inputSKU, inputDescription, inputPrice, inputUOM, inputQuantity);
	//				PartTable.AddItem(*newPart);
	//			}
	//			else {
	//				Part* newPart = new Part(inputSKU, inputDescription, inputPrice, inputUOM);
	//				PartTable.AddItem(*newPart);
	//			}
	//		}

	//		// Remove part
	//		else if (userChoice == 2) {
	//			cout << "Enter SKU of item you would like to remove: " << endl;
	//			cin >> inputSKU;
	//			retrieved_part = PartTable.GetItem(inputSKU);
	//			cout << "Item removed: " << retrieved_part->GetPartInfo() << endl;
	//			retrieved_part->resetPart();
	//		}

	//		// Get part
	//		else if (userChoice == 3) {
	//			cout << "Enter the SKU of item you would like to get: " << endl;
	//			cin >> inputSKU;
	//			retrieved_part = PartTable.GetItem(inputSKU);
	//			cout << "Item retrieved: " << retrieved_part->GetPartInfo() << endl;
	//		}

	//		// Get list length
	//		else if (userChoice == 4) {
	//			cout << "There are " << PartTable.GetLength() << " items in the list" << endl;
	//		}

	//		// Bad input handle
	//		else
	//		{
	//			cout << "Invalid selection." << endl;
	//		}
	//		PartTable.print();
	//		cout << endl;
	//		cout << "Would you like to continue? y/n " << endl;
	//		cin >> userContinuePrompt; // ima try it. Look at what I do and see if it's stupid and if I make mistakes
	//		// the item remains in the hash? Like, does it not convert to a -1?
	//		//

	//		// Break if user chooses to
	//		if (userContinuePrompt == "n")
	//		{
	//			userContinue = false;
	//		}

	//	}
	//	if (retrieved_part)
	//	return 0;
	//}
	//// 2) Chained Hash Table
	//else if (userChoice == 2) {
	//	// Program Loop
	//	while (userContinue) {
	//		cout << "Enter 1 to add a new part" << endl;
	//		cout << "Enter 2 to remove a part" << endl;
	//		cout << "Enter 3 to get a part" << endl;
	//		cout << "Enter 4 to get the length" << endl;
	//		cin >> userChoice;

	//		// Add new part
	//		if (userChoice == 1) {
	//			cout << "Enter the SKU: " << endl;
	//			cin >> inputSKU;
	//			cout << "Enter the description: " << endl;
	//			cin >> inputDescription;
	//			cout << "Enter the price: " << endl;
	//			cin >> inputPrice;
	//			cout << "Enter the unit of measure: " << endl;
	//			cin >> inputUOM;
	//			cout << "Do you wish to input the quantity on hand? (y/n)" << endl;
	//			cin >> userWantToInputQuantity;
	//			if (userWantToInputQuantity == "y")
	//			{
	//				cout << "Enter the quantity on hand: " << endl;
	//				cin >> inputQuantity;
	//				Part* newPart = new Part(inputSKU, inputDescription, inputPrice, inputUOM, inputQuantity);
	//				ChainedPartTable.AddItem(*newPart);
	//			}
	//			else {
	//				Part* newPart = new Part(inputSKU, inputDescription, inputPrice, inputUOM);
	//				ChainedPartTable.AddItem(*newPart);
	//			}
	//		}

	//		// Remove part
	//		else if (userChoice == 2) {
	//			cout << "Enter SKU of item you would like to remove: " << endl;
	//			cin >> inputSKU;
	//			*retrieved_part = ChainedPartTable.RemoveItem(inputSKU);
	//			cout << "Item removed: " << retrieved_part->GetPartInfo() << endl;\
	//		}

	//		// Get part
	//		else if (userChoice == 3) {
	//			Part tempPart;
	//			cout << "Enter the SKU of item you would like to get: " << endl;
	//			cin >> inputSKU;
	//			tempPart = ChainedPartTable.GetItem(inputSKU)->GetItem(inputSKU)->part;
	//			if (tempPart.getSKU() == inputSKU) {
	//				cout << "Item retrieved: " << tempPart.GetPartInfo() << endl;
	//			}
	//			else {
	//				cout << "Could not find " << inputSKU << endl;
	//			}
	//		}

	//		// Get list length
	//		else if (userChoice == 4) {
	//			cout << "There are " << ChainedPartTable.GetLength() << " items in the list" << endl;
	//		}

	//		// Bad input handle
	//		else
	//		{
	//			cout << "Invalid selection." << endl;
	//		}
	//		ChainedPartTable.print();
	//		cout << endl;
	//		cout << "Would you like to continue? y/n " << endl;
	//		cin >> userContinuePrompt; // ima try it. Look at what I do and see if it's stupid and if I make mistakes
	//		// the item remains in the hash? Like, does it not convert to a -1?
	//		//

	//		// Break if user chooses to
	//		if (userContinuePrompt == "n")
	//		{
	//			userContinue = false;
	//		}

	//	}
	//	return 0;
	//}
	//else {
	//	cout << "Invalid option. Try again." << endl;
	//	return 0;
	//}

	for (int i = 0; i < 50; i++) {

	}
}