#pragma once
#include <iostream>
#include <vector>

#include "Part.h"
#include "LinkedList.h"

using namespace std;

template<typename T>
class ChainedHashTable
{
public:
    int numChecks = 0;
    LinkedList* hashArray;
    int arraySize;

    ChainedHashTable()
    {
        hashArray = new LinkedList[100];
        arraySize = 100;
    }
    ChainedHashTable(int input)
    {
        hashArray = new LinkedList[input];
        arraySize = input;
    }
    ~ChainedHashTable() {
        //for (int i = 0; i < arraySize; i++) { 
        //    delete hashArray[i];
        //}
        delete[] hashArray; 
    }

    int hashfunct(string key, int& count) {
        int index = 0;
        for (size_t i = 0; key[i]; i++)
        {
            index += key[i];
        }
        index %= arraySize;
        if (hashArray[index].IsEmpty())
        {
            count += 1;
            return index;
        }
        else
        {
            while (hashArray[index].IsEmpty() == true)
            {
                count += 1;
                index = (index + 1) % arraySize;
                if (count = arraySize - 1)
                {
                    return -1;
                }
            }
        }
        return index;
    }

    int AddItem(Part inPart)
    {
        int count = 0;
        int index = 0;
        string itemName = inPart.getSKU();
        index = hashfunct(itemName, count);
        if (index == -1)
        {
            cout << "Array Full" << endl;
        }
        else
        {
            hashArray[index].AddItem(inPart); //insert the key in the index returned
            cout << endl;
            cout << "Element " << itemName << " inserted at index " << index << " No.of Places Searched is " << count << endl;
            numChecks += count;
            return 0;
        }
    }
    LinkedList* GetItem(string SKU)
    {
        int count = 0;
        int found = 1;
        int index = 0;
        for (size_t i = 0; SKU[i]; i++)
        {
            index += SKU[i];
        }
        index %= arraySize;
        if (hashArray[index].IsInList(SKU))
        {
            count += 1;
        }
        else
        {
            while (!(hashArray[index].IsInList(SKU)))
            {
                count += 1;
                index = (index + 1) % arraySize;
                if (count == arraySize - 1)
                {
                    //cout << "Element not found!" << endl;
                    found = 0;
                }
            }

        }
        numChecks += count;
        if (found == 1)
        {
            cout << "Item " << SKU << " found at index " << index << "." << endl;
            return &hashArray[index];
        }
        if (found == 0)
        {
            cout << "Item " << SKU << " not found!" << endl;
            return nullptr;
        }
    }

    Part RemoveItem(string itemName)
    {
        int count = 0;
        int found = 1;
        int index = 0;
        Part retPart;
        for (size_t i = 0; itemName[i]; i++)
        {
            index += itemName[i];
        }
        index %= arraySize;
        if (hashArray[index].IsInList(itemName))
        {
            count += 1;
        }
        else
        {
            while (!(hashArray[index].IsInList(itemName)))
            {
                count += 1;
                index = (index + 1) % arraySize;
                if (count == arraySize - 1)
                {
                    //cout << "Element not found!" << endl;
                    found = 0;
                }
            }

        }
        numChecks += count;
        if (found == 1)
        {
            cout << "Item " << itemName << "found at index " << index << "." << endl;
            retPart = hashArray[index].remove(itemName);
            return retPart;
        }
        if (found == 0)
        {
            cout << "Item " << itemName << "not found!" << endl;
            return retPart;
        }
    }

    int GetLength() {
        int numItems = 0;
        for (int i = 0; i < arraySize; i++) {
            if (!hashArray[i].IsEmpty()) {
                numItems += hashArray[i].Size();
            }
        }
        return numItems;
    }

    void print()
    {
        cout << "HashTable :" << endl;
        for (int i = 0; i < arraySize; ++i)
            if (!(hashArray[i].IsEmpty())) {
                hashArray[i].display();
            }
        cout << endl;
    }
};