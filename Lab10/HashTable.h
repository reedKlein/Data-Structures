#pragma once
#pragma once
#include <iostream>
#include <vector>

#include "Part.h"

using namespace std;

template<typename T>
class HashTable
{
public:
    int numChecks = 0;
    Part* hashArray;
    int arraySize;

    HashTable()
    {
        hashArray = new Part[100];
        arraySize = 100;
    }
    HashTable(int input)
    {
        hashArray = new Part[input];
        arraySize = input;
    }
    ~HashTable() {
        delete[] hashArray;
    }

    int hashfunct(string key, int& count) {
        int index = 0;
        for (size_t i = 0; key[i]; i++)
        {
            index += key[i];
        }
        index %= arraySize;
        if (hashArray[index].getSKU() == "")
        {
            count += 1;
            return index;
        }
        else
        {
            while (string(hashArray[index]) != "")
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
            hashArray[index] = inPart; //insert the key in the index returned
            cout << endl;
            cout << "Element " << inPart.getSKU() << " inserted at index " << index << " No.of Places Searched is " << count << endl;
            numChecks += count;
            return 0;
        }
    }
    Part* GetItem(string SKU)
    {
        int count = 0;
        int found = 1;
        int index = 0;
        for (size_t i = 0; SKU[i]; i++)
        {
            index += SKU[i];
        }
        index %= arraySize;
        if (hashArray[index].getSKU() == SKU)
        {
            count += 1;
        }
        else
        {
            while (hashArray[index].getSKU() != SKU)
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

    Part* RemoveItem(string itemName)
    {
        int count = 0;
        int found = 1;
        int index = 0;
        Part* retPart;
        for (size_t i = 0; itemName[i]; i++)
        {
            index += itemName[i];
        }
        index %= arraySize;
        if (hashArray[index].getSKU() == itemName)
        {
            count += 1;
        }
        else
        {
            while (hashArray[index].getSKU() != itemName)
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
            retPart = &hashArray[index];
            hashArray[index] = -1;
            return retPart;
        }
        if (found == 0)
        {
            cout << "Item " << itemName << "not found!" << endl;
            return nullptr;
        }
    }

    int GetLength() {
        int numItems = 0;
        for (int i = 0; i < arraySize; i++) {
            if (hashArray[i].getSKU() != "") {
                numItems += 1;
            }
        }
        return numItems;
    }

    void print()
    {
        cout << "HashTable :" << endl;
        for (int i = 0; i < arraySize; ++i)
            if (hashArray[i].getSKU() != "") {
                hashArray[i].display();
            }
        cout << endl;
    }
};