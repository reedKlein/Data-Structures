#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>
#include <fstream>
#include <string>

#include "BinaryTree.h"
#include "NodeData.h"

using namespace std;

//-------------------------------------------------------------------//
// Lab09 Solution: Basketbal 3: Electric Boogalootwo                 //
// Authors: Liam Sheerajin, Reed Klein, Dominic Boyte, Alex Davison  //
// Lab Period: Section 002 | Monday 2:30 PM - 5:30 PM                //
// Group Number: 13                                                  //
// This program takes in an input book, and allows the user to print //
// its contents in ascending or descening order, or serach for a     //
// specific word. The words shown will also be accompanied by its    //
// amount of times they appear in the book.                          //
//-------------------------------------------------------------------//

// Function to add NodeData into binary tree. Clears the data of the inserted
// temp node from main (not from the tree).
void insertNodeDataIntoBinaryTree(NodeData& data, BinaryTree<NodeData>& BT) {
	if (BT.Find(data) == nullptr) {
		BT.root = BT.insert(BT.root, data);
	}
	else {
		BT.Find(data)->key.m_count++;
	}
	data.reset();
}

int main() {
	// Initialize variables
	ifstream bookFile;
	string fileName;
	string buffer;
	string line;
	ofstream outFile;
	string searchWord;


	// Program loop
	do {
		// Construct tree
		BinaryTree<NodeData> BT;

		//Ask for the file name
		cout << "Enter the file name: ";
		cin >> fileName;

		// Opens the file
		bookFile.open(fileName);

		// While loop confirming the validity of the file named
		while (bookFile.fail()) {
			cout << "You donkey! That is not a valid file. Please enter a valid file name: ";
			cin >> fileName;
			bookFile.open(fileName);
		}

		// Getting all lines in the book
		while (getline(bookFile, line)) {

			// Skips line if it's blank
			if (line.length() == 0) {
				// No-op
			}

			// Iterates through lines of the body of the text
			else {
				NodeData tempData;
				for (int ii = 0; ii < line.length(); ii++) {
					// If space is found, insert word into tree
					if (line[ii] == ' ') {
						insertNodeDataIntoBinaryTree(tempData, BT);
					}
					// Add character to m_string in the data-holding object
					else {
						// Do not include punctuation!
						if (line[ii] != '.' && line[ii] != ',' && line[ii] != '!' && line[ii] != '?' && line[ii] != '\"' && line[ii] != '\'') {
							// All characters will be lowercase
							tempData.m_word.push_back(tolower(line[ii]));
						}
					}
				}
				// Adds word at the end of the line
				insertNodeDataIntoBinaryTree(tempData, BT);
			}
		}

		// Close book.txt
		bookFile.close();

		// CardCatalog.txt ouput handle
		// Creates or clears any content within CardCatalog.txt
		outFile.open("CardCatalog.txt", ios::trunc);
		outFile.close();
		outFile.open("CardCatalog.txt");
		outFile << "File Name: " << fileName << endl;

		do{
			cout << "What would you like to do?" << endl;
			cout << "See a particular word: 1" << endl;
			cout << "See all words in ascending order: 2" << endl;
			cout << "See all words in descending order: 3" << endl;
			cin >> buffer;

			// Check count for a specific word
			if(buffer == "1"){
				cout << "What word would you like to check? (Type search in all lowercase, or word will not be found)" << endl;
				cin >> searchWord;

				if (BT.Find(searchWord) == nullptr) {
					cout << "Word is not within the tree" << endl;
				}
				else {
					cout << "There are " << BT.Find(searchWord)->key.m_count << " instance(s) of " << searchWord << endl;
				}
			}
			// Asecnding all words
			else if(buffer == "2"){
				BT.ret_vector.clear();
				BT.getAllAscending(BT.root);
				for (int i = 0; i < BT.ret_vector.size(); i++) {
					cout << BT.ret_vector.at(i).m_word << " appeared " << BT.ret_vector.at(i).m_count << " times\n";
				}
			}
			// Descending all words
			else if(buffer == "3"){
				BT.ret_vector.clear();
				BT.getAllDescending(BT.root);
				for (int i = 0; i < BT.ret_vector.size(); i++) {
					cout << BT.ret_vector.at(i).m_word << " appeared " << BT.ret_vector.at(i).m_count << " times\n";
				}
			}
			else{
				cout << "invalid input";
				buffer == "invalidInput"; //no dont :(
			}
		} while (buffer == "invalidInput");

		// Prompts user if they would like to enter another book
		do {
			cout << "Would you like to enter another book??? (y/n)\n";
			cin >> buffer;
		} while (buffer != "n" && buffer != "y");

		// Recurse if given anything but "n" (so we can assume "y" from our previous do-while loop)
	} while (buffer != "n");
}