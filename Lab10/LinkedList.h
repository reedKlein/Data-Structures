#pragma once
#pragma once
#include <exception>
#include <iostream>
#include <string>
#include <ctime>

#include "Part.h"

using namespace std;

// Exception thrown when user tries to access itme in empty list
struct  EmptyList : public exception {
	const char* what() const throw() {
		return "List is empty";
	}
};

class LinkedList {
public:
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
		while (delNode) {
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
			if (head) {
				// head has no previous, so set to null ptr
				head->prev = nullptr;
			}
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

	Part remove(string SKU) {
		node* currNode = this->GetItem(SKU);
		if (currNode) {
			node* nextNode = currNode->next;
			node* prevNode = currNode->prev;

			// Bridge gap between nodes
			if (nextNode && prevNode) {
				currNode->prev->next = nextNode;
				currNode->next->prev = prevNode;
			}

			// Set head to next node (as there is no previous so the current node is the head)
			else if (nextNode) {
				head = nextNode;
			}
			Part partData = currNode->part;

			delete currNode;
			return partData;
		}
		Part bogusPart;
		return bogusPart;
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
			catch (EmptyList & e) {
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
			catch (EmptyList & e) {
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
			catch (EmptyList & e) {
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
		while (printNode)
		{
			cout << printNode->part.GetPartInfo();
			printNode = printNode->next;
		}
		cout << endl;
	}

	void display() {
		node* currNode = head;
		//display each by going through head while (head)
		cout << "#############################################################" << endl;
		while (currNode) {
			currNode->part.display();
			cout << "#############################################################" << endl;
			currNode = currNode->next;
		}
	}
};