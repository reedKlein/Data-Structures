#include "HashTable.h"
#include "BinaryTree.h"

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

//-------------------------------------------------------------------//
// Lab10 Solution: Naboo Lalhpa: Electric Boogalootwo                //
// Authors: Liam Sheerajin, Reed Klein, Dominic Boyte, Alex Davison  //
// Lab Period: Section 002 | Monday 2:30 PM - 5:30 PM                //
// Group Number: 13                                                  //
// This program will manipulate a hash table, and return certain     //
// stats involving performance to the user.                          //
//-------------------------------------------------------------------//

int main() {
    HashTable intTable; //object of hashtable
    int TreeFirstInsert;
    int TreeSecondInsert;
    int TreeDelete;
    int TableFirstInsert;
    int TableSecondInsert;
    int TableDelete;
    BinaryTree<int> intTree;
    vector<int> randNums;
    int randomNum;
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        randomNum = rand() % 1000;
        while (find(randNums.begin(), randNums.end(), randomNum) != randNums.end())
        {
            randomNum = rand() % 1000;
        }
        randNums.push_back(randomNum);
    }
    for (int i = 0; i < 50; i++)
    {
        intTable.insert(randNums[i]);
        intTree.insert(intTree.root, randNums[i]);
    }
    TableFirstInsert = intTable.numChecks;
    TreeFirstInsert = intTree.getSumOfSpotsChecked();
    cout << endl;
    cout << "Hash Table number of spots checked to insert first 50: " << TableFirstInsert << endl;
    cout << "Binary Tree number of spots checked to insert first 50: " << TreeFirstInsert << endl;
    cout << endl;
    for (int i = 0; i < 50; i++)
    {
        if (randNums[i] % 7 == 0)
        {
            intTable.remove(randNums[i]);
            intTree.remove(intTree.root, randNums[i]);
        }
    }
    TableDelete = intTable.numChecks - TableFirstInsert;
    TreeDelete = intTree.getSumOfSpotsChecked() - TreeFirstInsert;
    cout << endl;
    cout << "Hash Table number of spots checked to delete: " << TableDelete << endl;
    cout << "Binary Tree number of spots checked to delete: " << TreeDelete << endl;
    cout << endl;
    for (int i = 50; i < 100; i++)
    {
        intTable.insert(randNums[i]);
        intTree.insert(intTree.root, randNums[i]);
    }
    TableSecondInsert = intTable.numChecks - TableFirstInsert - TableDelete;
    TreeSecondInsert = intTree.getSumOfSpotsChecked() - TreeFirstInsert - TreeDelete;
    cout << endl;
    cout << "Hash Table number of spots checked to insert: " << TableSecondInsert << endl;
    cout << "Binary Tree number of spots checked to insert: " << TreeSecondInsert << endl;
    cout << endl;
}
