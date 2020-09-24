#pragma once
#include <exception>
#include <iostream>
#include <string>
#include <ctime>
#define RANGE 255

using namespace std;

// Exception thrown when user tries to access itme in empty list
struct  EmptyList : public exception {
	const char* what() const throw() {
		return "List is empty";
	}
};

class LinkedList {
public:
	struct StudentID {
		StudentID* next;
		StudentID* prev;
		string m_firstName;
		string m_lastName;
		int m_MNumber;
	};

	StudentID* head;
	// SeeCtr used to count number of times SeeNext or SeePrev has been used
	// probably shouldn't be necessary but its here for now, TODO: Remove SeeCtr
	int SeeCtr = 0;
	// SeeNode used as the starting point for SeeNext and SeePrev calls
	StudentID* SeeNode = head;

	//Default constructor
	LinkedList() {
		head = nullptr;
		SeeNode = nullptr;
		SeeCtr = 0;
	}
	//Deconstructor frees all nodes in list
	~LinkedList() {
		StudentID* delNode = head;
		StudentID* prevNode;
		while (delNode) {
			prevNode = delNode;
			delNode = delNode->next;
			delete prevNode;

		}
	}

	// Function to swap the StudentIDs
	StudentID* swap(StudentID* ID1, StudentID* ID2)
	{
		StudentID* tmp = ID2->next;
		ID2->next = ID1;
		ID1->next = tmp;
		return ID2;
	}

	// Function to perform a bubble sort
	void bubbleSort(StudentID** head, bool ascend = true)
	{
		StudentID** h;
		int i, j, swapped;

		for (i = 0; i <= 50; i++)
		{

			h = head;
			swapped = 0;

			for (j = 0; j < 50 - i - 1; j++)
			{

				StudentID* p1 = *h;
				StudentID* p2 = p1->next;

				if (ascend && p1->m_lastName > p2->m_lastName)
				{

					/* update the link after swapping */
					*h = swap(p1, p2);
					swapped = 1;
				}
				else if (!ascend && p1->m_lastName < p2->m_lastName) {

					/* update the link after swapping */
					*h = swap(p1, p2);
					swapped = 1;
				}

				h = &(*h)->next;
			}

			/* break if the loop ended without any swap */
			if (swapped == 0)
				break;
		}
	}

	// function to insert a new node in sorted way in 
	// a sorted doubly linked list 
	void sortedInsert(StudentID** head_ref, StudentID* newNode, bool ascend)
	{
		StudentID* current;

		if (ascend) {
			// if list is empty 
			if (*head_ref == NULL)
				*head_ref = newNode;

			// if the node is to be inserted at the beginning 
			// of the doubly linked list 
			else if ((*head_ref)->m_lastName >= newNode->m_lastName) {
				newNode->next = *head_ref;
				newNode->next->prev = newNode;
				*head_ref = newNode;
			}

			else {
				current = *head_ref;

				// locate the node after which the new node 
				// is to be inserted 
				while (current->next != NULL &&
					current->next->m_lastName < newNode->m_lastName)
					current = current->next;

				/*Make the appropriate links */

				newNode->next = current->next;

				// if the new node is not inserted 
				// at the end of the list 
				if (current->next != NULL)
					newNode->next->prev = newNode;

				current->next = newNode;
				newNode->prev = current;
			}
		}

		else {
			// if list is empty 
			if (*head_ref == NULL)
				*head_ref = newNode;

			// if the node is to be inserted at the beginning 
			// of the doubly linked list 
			else if ((*head_ref)->m_lastName <= newNode->m_lastName) {
				newNode->next = *head_ref;
				newNode->next->prev = newNode;
				*head_ref = newNode;
			}

			else {
				current = *head_ref;

				// locate the node after which the new node 
				// is to be inserted 
				while (current->next != NULL &&
					current->next->m_lastName > newNode->m_lastName)
					current = current->next;

				/*Make the appropriate links */

				newNode->next = current->next;

				// if the new node is not inserted 
				// at the end of the list 
				if (current->next != NULL)
					newNode->next->prev = newNode;

				current->next = newNode;
				newNode->prev = current;
			}
		}

	}

	// function to sort a doubly linked list using insertion sort 
	void insertionSort(StudentID** head_ref, bool ascend = true)
	{
		// Initialize 'sorted' - a sorted doubly linked list 
		StudentID* sorted = NULL;

		// Traverse the given doubly linked list and 
		// insert every node to 'sorted' 
		StudentID* current = *head_ref;
		while (current != NULL) {

			// Store next for next iteration 
			StudentID* next = current->next;

			// removing all the links so as to create 'current' 
			// as a new node for insertion 
			current->prev = current->next = NULL;

			// insert current in 'sorted' doubly linked list 
			sortedInsert(&sorted, current, ascend);

			// Update current 
			current = next;
		}

		// Update head_ref to point to sorted doubly linked list 
		*head_ref = sorted;
	}

	// Function to merge two linked lists  
	StudentID* merge(StudentID* first, StudentID* second, bool ascend)
	{
		// If first linked list is empty  
		if (!first)
			return second;

		// If second linked list is empty  
		if (!second)
			return first;
		
		if (ascend) {
			// Pick the smaller value  
			if (first->m_lastName < second->m_lastName)
			{
				first->next = merge(first->next, second, ascend);
				first->next->prev = first;
				first->prev = NULL;
				return first;
			}
			else
			{
				second->next = merge(first, second->next, ascend);
				second->next->prev = second;
				second->prev = NULL;
				return second;
			}
		}
		else {
			// Pick the smaller value  
			if (first->m_lastName > second->m_lastName)
			{
				first->next = merge(first->next, second, ascend);
				first->next->prev = first;
				first->prev = NULL;
				return first;
			}
			else
			{
				second->next = merge(first, second->next, ascend);
				second->next->prev = second;
				second->prev = NULL;
				return second;
			}
		}
	}

	// Function to do merge sort  
	StudentID* mergeSort(StudentID* tempID, bool ascend = true)
	{
		if (!tempID || !tempID->next)
			return tempID;
		StudentID* second = split(tempID);

		// Recur for left and right halves  
		tempID = mergeSort(tempID, ascend);
		second = mergeSort(second, ascend);

		// Merge the two sorted halves  
		return merge(tempID, second, ascend);
	}

	// Split a doubly linked list (DLL) into 2 DLLs of  
	// half sizes  
	StudentID* split(StudentID* head)
	{
		StudentID* fast = head, * slow = head;
		while (fast->next && fast->next->next)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		StudentID* temp = slow->next;
		slow->next = NULL;
		return temp;
	}

	void AddItem(string firstName, string lastName, int MNumber) {
		// newNode is the node being added to list
		StudentID* newNode;
		// nodePtr mvoes through list as it tries to find spot for newNode
		StudentID* nodePtr;
		// Initializes newNode with all necessary values, should use an overloaded constructor
		// TODO: make node constructor and replace following lines
		newNode = new StudentID;
		newNode->m_firstName = firstName;
		newNode->m_lastName = lastName;
		newNode->m_MNumber = MNumber;
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
			while (nodePtr->next && nodePtr->next->next)
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
	StudentID* GetItem(string lastName) {
		//nodePtr will iterate through list to find item
		StudentID* nodePtr = head;
		// ret_ptr will preserve the node to be returned
		StudentID* ret_ptr = head;
		// if empty list(no head), return nullptr
		if (!head) {
			return nullptr;
		}
		// if head is the node we want to remove, we need to adjust list
		if (head->m_lastName == lastName) {
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
				if (nodePtr->m_lastName == lastName)
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

	StudentID remove(string lastName) {
		StudentID* currNode = this->GetItem(lastName);
		if (currNode) {
			StudentID* nextNode = currNode->next;
			StudentID* prevNode = currNode->prev;

			// Bridge gap between nodes
			if (nextNode && prevNode) {
				currNode->prev->next = nextNode;
				currNode->next->prev = prevNode;
			}

			// Set head to next node (as there is no previous so the current node is the head)
			else if (nextNode) {
				head = nextNode;
			}
			StudentID returnID = *currNode;

			delete currNode;
			return returnID;
		}
	}
	// looks just to see if item is in list
	bool IsInList(string lastName) {
		// nodePtr will iterate thru list
		StudentID* nodePtr = head;
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
			if (nodePtr->m_lastName == lastName)                                // TODO: NOT SURE IF RIGHT
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
		StudentID* nodePtr = head;
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
	StudentID* SeeNext() {
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
	StudentID* SeePrev() {
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

	StudentID* SeeAt(int spot) {
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

	StudentID* lastNode(StudentID* n)
	{
		while (n && n->next)
			n = n->next;
		return n;
	}

	/* Function to print the list */
	void printList(StudentID* n)
	{
		while (n != NULL)
		{
			cout << n->m_lastName << ", " << n->m_firstName << ": " << n->m_MNumber << " -> ";
			n = n->next;
		}
		cout << endl;
	}

};