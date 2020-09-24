#pragma once
#include <iostream>
#include <vector>
using namespace std;

class HashTable
{
public:
    int numChecks;
    int k;
    int a[500]; //declaring array of 500 items
    HashTable() //constructor
    {
        //fill it with -1 indicating it is empty
        for (int i = 0; i < 500; ++i)
            a[i] = -1;
        numChecks = 0;
        k = 0;
    }
    int hashfunct(int k, int& c)
    {
        int index;
        index = k % 500;    //calculate index using k%500
        if (a[index] == -1) //if it is empty then return it
        {
            c += 1;
            return index;
        }
        else //linear probing searching until empty index is found
        {
            while (a[index] != -1) //if not empty then loop until we find empty index
            {
                c += 1;                    //count number of places searched
                index = (index + 1) % 500; // search in circular manner
                if (c == 499)              //if all elements traversed means array is full
                    return -1;
            }
        }
        return 0;
    }

    int insert(int k)
    {
        int c = 0, index;
        index = hashfunct(k, c); //use hashfunct to find index
        if (index == -1) {
            cout << endl;
            cout << endl;
            cout << "Array Full" << endl; //if -1 means array is full
            cout << endl;
            cout << endl;
            return 1;
        }
        else
        {
            a[index] = k; //insert the key in the index returned
            cout << endl;
            cout << "Element " << k << " inserted at index " << index << " No.of Places Searched is " << c << endl;
            numChecks += c;
            return 0;
        }
    }
    int find(int k)
    {
        int c = 0, f = 1;
        int index;
        index = k % 500; //calculate index using k%500
        if (a[index] == k)
        { //if it is equal to key then return it
            c += 1;
        }
        else
        {
            while (a[index] != -k)
            {           //if not empty then loop until we find index of the key
                c += 1; //count number of places searched
                index = (index + 1) % 500;
                if (c == 500)
                {
                    cout << "Element not found" << endl;
                    f = 0;
                    return 1;
                }
            }
        }
        if (f == 1)
        {
            cout << "Element " << k << " Found at index " << index << " number of spots checked is " << c << endl;
            return 0;
        }
    }

    int remove(int k)
    {
        int c = 0, f = 1;
        int index;
        index = k % 500; //calculate index using k%500
        if (a[index] == k)
        { //if it is equal to key then delete it by replacing it with -1
            c += 1;
            a[index] = -1;
        }
        else
        {
            while (a[index] != -k)
            {           //if not empty then loop until we find index of the key when found remove it by replacing it with -1
                c += 1; //count number of places searched
                index = (index + 1) % 500;
                if (c == 500)
                {
                    cout << "Element not found" << endl;
                    f = 0;
                    return 1;
                }
            }
            if (f == 1)
                a[index] = -1;
        }
        if (f == 1)
        {
            cout << "Element " << k << " removed from index " << index << " number of spots checked is " << c << endl;
            return 0;
        }
        numChecks += c;
    }

    void print()
    {
        cout << "HashTable :" << endl;
        for (int i = 0; i < 500; ++i)
            cout << a[i] << " ";
        cout << endl;
    }
};

