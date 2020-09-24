#pragma once
#include <exception>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;


// Exception thrown when user tries to access itme in empty list
struct  EmptyList : public exception {
	const char* what() const throw() {
		return "List is empty";
	}
};

class Part {
private:
	string SKU;
	string description;
	int price;
	string UOM;
	int quantityOnHand;
	int leadTime;
public:
	Part() {
		SKU = "";
		description = "";
		price = 0;
		UOM = "";
		quantityOnHand = 0;
		leadTime = 0;
	}
	Part(string SKU, string description, int price, string UOM, int quantityOnHand = 0) {
		this->SKU = SKU;
		this->description = description;
		this->price = price;
		this->UOM = UOM;
		this->quantityOnHand = quantityOnHand;
	}

	string getSKU() {
		return SKU;
	}

	string GetPartInfo() {
		string ret_str = SKU + ": " + description;
		return ret_str;
	}
	int getPrice() {
		return price;
	}
	bool InStock() {
		return quantityOnHand > 0;
	}

	bool Available(string currDate) {
		size_t currentIndex = 0;
		size_t previousIndex = 0;
		
		//Find day
		currentIndex = currDate.find('/');
		int month = stoi(currDate.substr(0, currentIndex));

		//Find month
		previousIndex = currentIndex + 1;
		currentIndex = currDate.find('/', previousIndex);
		int day = stoi(currDate.substr(previousIndex, currentIndex));

		//Find year
		previousIndex = currentIndex + 1;
		int year = stoi(currDate.substr(previousIndex, currDate.size()));

		//Get total days from jan 1st
		int numDays = day + getNumberOfDays(month, year);

		//Product is available
		if (quantityOnHand > 0) {
			return true;
		}
		// Product will/wont be available then
		else
		{
			time_t now = time(0);
			tm* ltm = localtime(&now);
			return numDays > (leadTime + ltm->tm_yday);
		}

	}

	//Function to return total number of days
	int getNumberOfDays(int month, int year)
	{
		if(month == 1) {
			return 31;
		}
		//Leap year condition, if month is 2
		if( month == 2) {
			if((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
				return 29 + getNumberOfDays(month - 1, year);
			}
			else {
				return 28 + getNumberOfDays(month - 1, year);
			}
		}
		//Months which have 31 days
		else if(month == 3 || month == 5 || month == 7 || month == 8
		           || month == 10 || month==12) {
			return 31 + getNumberOfDays(month - 1, year);
		}
		else {
			return 30 + getNumberOfDays(month - 1, year);
		}		
	} 

	bool operator==(Part const &obj) {
		return SKU == obj.SKU;
	}
	bool operator>(Part const& obj) {
		return SKU > obj.SKU;
	}
	bool operator<(Part const& obj) {
		return SKU < obj.SKU;
	}

	void display() {
		cout <<"#-----------------------------------------------------------#"<<endl;
		cout <<"# Price: " << price << endl;
		cout <<"# Stock Keeping Number: " << SKU << endl;
		cout <<"# Sold by the " << UOM << endl;
		cout <<"# " << description << endl;
		cout <<"#-----------------------------------------------------------#"<<endl;
	}
};

class LinkedList {
private:
	struct node {
		struct node* next;
		struct node* prev;
		Part part;
	};
	node* head;
	// SeeCtr used to count number of times SeeNext or SeePrev has been used
	// probably shouldn't be necessary but its here for now, TODO: Remove SeeCtr
	int SeeCtr = 0;
	// SeeNode used as the starting point for SeeNext and SeePrev calls
	node* SeeNode = head;

public:
	//Default constructor
	LinkedList() {
		head = nullptr;
		SeeNode = nullptr;
		SeeCtr = 0;
	}
	//Deconstructor frees all nodes in list
	~LinkedList() {
		node* delNode = head;
		node* prevNode;
		while (!delNode) {
			prevNode = delNode;
			delNode = delNode->next;
			delete prevNode;
			
		}
	}
	void AddItem(Part item) {
		// newNode is the node being added to list
		node* newNode;
		// nodePtr mvoes through list as it tries to find spot for newNode
		node* nodePtr;
		// Initializes newNode with all necessary values, should use an overloaded constructor
		// TODO: make node constructor and replace following lines
		newNode = new node;
		newNode->part = item;
		newNode->next = nullptr;
		newNode->prev = nullptr;

		// if list is empty (no head), newNode becomes head
		if (!head)
		{
			head = newNode;
			// should I delete newNode? TODO: decide if I should delete newNode
		}
		else
		{
			// nodePtr is what will iterate through the list, so start it at head
			nodePtr = head;
			// go to next item if next exists and next's value is less than newNode's value
			while (nodePtr->next && newNode->part > nodePtr->next->part)
			{
				// set nodePtr to next item
				nodePtr = nodePtr->next;
			}
			// once we pass that loop, we have found the spot to insert newNode
			// we will insert newNode after nodePtr, so if nodePtr has a next,
			// we need newNode to assume nodePtr's next and that next's prev must point back to newNode
			if (nodePtr->next) {
				newNode->next = nodePtr->next;
				newNode->next->prev = newNode;
			}
			// insert newNode after nodePtr
			nodePtr->next = newNode;
			// newNode's previous is nodePtr
			newNode->prev = nodePtr;
		}

	}
	// finds given item, removes it from list, returns it
	node* GetItem(string SKU) {
		//nodePtr will iterate through list to find item
		node* nodePtr = head;
		// ret_ptr will preserve the node to be returned
		node* ret_ptr = head;
		// if empty list(no head), return nullptr
		if (!head) {
			return nullptr;
		}
		// if head is the node we want to remove, we need to adjust list
		if (head->part.getSKU() == SKU) {
			// adjust head to point to the next item
			head = head->next;
			// head has no previous, so set to null ptr
			head->prev = nullptr;
			// ret_ptr holds the original head, so return that
			return nodePtr;	
		}
		// enter if head is not item to be removed
		else {
			// continue if nodePtr exists
			while (nodePtr)
			{
				// if nodePtr is the one we want to remove, enter
				if (nodePtr->part.getSKU() == SKU)
				{
					// ret_ptr preserves value of nodePtr
					ret_ptr = nodePtr;
					// adjust nodePtr's next's prev to point to nodePtr's prev
					nodePtr->next->prev = nodePtr->prev;
					// adjust nodePtr's prev's next to point to nodePtr's next
					nodePtr->prev->next = nodePtr->next;
					delete nodePtr;
					return ret_ptr;
				}
				else {
					nodePtr = nodePtr->next;
				}
			}
			// if item is never found, return nullptr
			return nullptr;
		}
		return nullptr;
	}
	// looks just to see if item is in list
	bool IsInList(string SKU) {
		// nodePtr will iterate thru list
		node* nodePtr = head;
		// if empty list (no head), return false
		if (!head)
		{
			return false;
		}
		// iterate thru list to find item
		// enter loop if nodePtr exists
		while (nodePtr)
		{
			// if nodePtr is what we're looking for, return true
			if (nodePtr->part.getSKU() == SKU)                                // TODO: NOT SURE IF RIGHT
			{
				return true;
			}
			// nodePtr isn't what we're looking for, so continue iterating thru list
			nodePtr = nodePtr->next;
		}
		// haven't found item, return false
		return false;

	}
	// returns true is no head (empty)
	bool IsEmpty() {
		if (!head) {
			return true;
		}
		return false;
	}
	// number of elements in array
	int Size() {
		node* nodePtr = head;
		int count = 0;
		if (!head) {
			return 0;
		}
		else {
			while (nodePtr) {
				count++;
				nodePtr = nodePtr->next;
			}
		}
		return count;
	}
	// displays next item in list
	node* SeeNext() {
		// if no item has ever been seen via seeNext or seePrev, need to start at head
		if (SeeCtr == 0) {
			SeeNode = head;
		}
		SeeCtr++;
		// is list is empty, throw EmptyList
		if (!head) {
			try {
				throw EmptyList();
			}
			catch (EmptyList& e) {
				cout << "EmptyList caught";
				cout << e.what() << endl;
			}
		// list not empty, enter
		}
		else {
			// enter if SeeNode has a next
			if (SeeNode->next)
			{
				// advance SeeNode and return
				SeeNode = SeeNode->next;
				return SeeNode;
			}
			// if SeeNode doesn't have a next, print error and return nullptr
			cout << "Null reached!" << endl;
			return nullptr;
		}

	}
	// same as SeeNext but in opposite direction
	node* SeePrev() {
		if (SeeCtr == 0) {
			SeeNode = head;
		}
		SeeCtr++;
		if (!head) {
			try {
				throw EmptyList();
			}
			catch (EmptyList& e) {
				cout << "EmptyList caught";
				cout << e.what() << endl;
			}
		}
		else {
			if (SeeNode->prev)
			{
				SeeNode = SeeNode->prev;
				return SeeNode;
			}
			cout << "Null reached!" << endl;
			return nullptr;
		}
	}

	node* SeeAt(int spot) {
		if (!head) {
			try {
				throw EmptyList();
			}
			catch (EmptyList& e) {
				cout << "EmptyList caught";
				cout << e.what() << endl;
			}
		}
		else {
			SeeNode = head;
			for (int i = 0; i < spot - 1; i++) {
				if (SeeNode->next) {
					SeeNode = SeeNode->next;
				}
				else
				{
					cout << "Null reached!" << endl;
					return nullptr;
				}
			}
			return SeeNode;
		}
		return nullptr;
	}

	void Reset() {
		SeeNode = head;
	}

	void Print() {
		string retString = "";
		node* printNode = head;
		while(printNode)
		{
			cout << printNode->part.GetPartInfo();
			printNode = printNode->next;
		}
		cout << endl;
	}

	void display() {
		node* currNode = head;
		//display each by going through head while (head)
		cout<<"#############################################################"<<endl;
		while(currNode) {
			currNode->part.display();
			cout<<"#############################################################"<<endl;
			currNode = currNode->next;
		}
	}
};