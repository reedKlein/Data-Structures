#include <iostream>
#include <chrono>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "LinkedList.h"

using namespace std;

// Driver Code 
int main()
{
    int input;
    string ascend;
    bool tryAgain = false;
    bool badInput = false;
    srand(time(NULL));

    string firstNameArray[26] = { "Alex","Charlie","Benjamin","Denny","Fred","Edward","Gary","Igy","Hannah","Kennedy","Jasmine","Maddie","Louis","Ned","Otto",
                                    "Quazar","Pele","Susan","Reed","Uman","Target","Will","Violet","Yar","Xray","Zzz" };
    string lastNameArray[26] = { "Anderson","Clark","Brown","Davis","Flores","Evans","Garcia","Ingram","Harris","King","Johnson","Miller","Lewis","Nelson",
                                    "Owens","Quinn","Perez","Smith","Robinson","Underwood","Taylor","Williams","Vasquez","Young","Xiong","Zimmerman" };

    // start with empty linked list
    LinkedList LL;

    //Student generator
    for (int i = 0; i < 50; i++) {
        LL.AddItem(lastNameArray[rand() % 26], firstNameArray[rand() % 26], rand() % 99999999);
    }

    do {
        tryAgain = false;

        // print list before sorting
        cout << "Linked list before sorting\n\n";
        LL.printList(LL.head);
        cout << endl;

        cout << "The list is always sorted by last name.\n";
        cout << "How would you like to sort the list?\n";
        cout << "1) Bubble sort\n";
        cout << "2) Insertion sort\n";
        cout << "3) Merge sort\n";
        cin >> input;

        //Bubble
        if (input == 1) {
            do {
                badInput = false;
                cout << "Would you like to sort in ascending or descending order? (a/d): ";
                cin >> ascend;
                if (ascend == "a") {
                    // sort the linked list
                    LL.bubbleSort(&LL.head, true);
                }
                else if (ascend == "d") {
                    // sort the linked list
                    LL.bubbleSort(&LL.head, false);
                }
                else {
                    cout << "Bad input! Try again.\n";
                    badInput = true;
                }
            } while (badInput);
        }

        //Insertion
        else if (input == 2) {
            do {
                cout << "Would you like to sort in ascending or descending order? (a/d): ";
                cin >> ascend;
                if (ascend == "a") {
                    // sort the linked list
                    LL.insertionSort(&LL.head, true);
                }
                else if (ascend == "d") {
                    // sort the linked list
                    LL.insertionSort(&LL.head, false);
                }
                else {
                    cout << "Bad input! Try again.\n";
                    badInput = true;
                }
            } while (badInput);
        }

        //Merge
        else if (input == 3) {
            do {
                cout << "Would you like to sort in ascending or descending order? (a/d): ";
                cin >> ascend;
                if (ascend == "a") {
                    // sort the linked list
                    LL.mergeSort(LL.head, true);
                }
                else if (ascend == "d") {
                    // sort the linked list
                    LL.mergeSort(LL.head, false);
                }
                else {
                    cout << "Bad input! Try again.\n";
                    badInput = true;
                }
            } while (badInput);
        }

        else {
            cout << "Bad input! Try again.\n";
            tryAgain = true;
        }
    } while (tryAgain);

    cout << endl << endl;
    // print list after sorting
    cout << "Linked list after sorting\n";
    LL.printList(LL.head);

    return 0;
}