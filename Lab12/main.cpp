#include <iostream>
#include <chrono>
#include<bits/stdc++.h>  
#include<string.h> 
typedef std::chrono::high_resolution_clock Clock;
using namespace std;

void swap(int* num1, int* num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void bubbleSort(int sortArray[], int arraySize)
{
    bool isSwapped;
    for(int i = 0; i < arraySize-1; i++)
    {
        isSwapped = false;
        for(int j = 0; j < arraySize-i-1; j++)
        {
            if (sortArray[j] > sortArray[j+1])
            {
                swap(&sortArray[j], &sortArray[j+1]);
                isSwapped = true;
            }
        }
        if(!isSwapped)
        {
            break;
        }
    }
    
}

void insertionSort(int sortArray[], int arraySize)
{
    int key;
    int j;
    for(int i = 1; i < arraySize; i++)
    {
        key = sortArray[i];
        j = i - 1;
        while(j >= 0 && sortArray[j] > key)
        {
            sortArray[j + 1] = sortArray[j];
            j -= 1;
        }
        sortArray[j+1] = key;
    }
}

void merge(int sortArray[], int lowBound, int midBound, int upperBound)
{
    int n1 = midBound - lowBound + 1;
    int n2 = upperBound - midBound;

    int L[n1];
    int R[n2];

    for(int i = 0; i < n1; i++)
    {
        L[i] = sortArray[i + lowBound];
    }

    for(int j = 0; j < n2; j++)
    {
        R[j] = sortArray[midBound + j + 1];
    }

    int i = 0;
    int j = 0;
    int k = lowBound;

    while(i < n1 && j < n2)
    {
        if( L[i] <= R[j])
        {
            sortArray[k] = L[i];
            i++;
        }
        else
        {
            sortArray[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1)
    {
        sortArray[k] = R[j];
        i++;
        k++;
    }
    while(j < n2)
    {
        sortArray[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int sortArray[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-1)/2;

        mergeSort(sortArray, l, m);
        mergeSort(sortArray, m+1, r);

        merge(sortArray, l, m, r);
    }
}


int partition(int sortArray[], int low, int high)
{
    int pivot = sortArray[high]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (sortArray[j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&sortArray[i], &sortArray[j]);  
        }  
    }  
    swap(&sortArray[i + 1], &sortArray[high]);  
    return (i + 1);  
}

void quickSort(int arr[], int low, int high)  
{  
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}

void countSort(int sortArray[], int arraySize, int numRange)
{
    int output[arraySize];
    int count[numRange+1];
    memset(output, 0, sizeof(output));
    memset(count, 0, sizeof(count));
   /*  for(int i = 0; i<numRange+1; i++)
    {
        count[i] = 0;
    } */
    for(int i = 0; sortArray[i]; ++i)
    {
        ++count[sortArray[i]];
    }
    for(int i = 1; i <= numRange; ++i)
    {
        count[i] += count[i-1];
    }
    for(int i = 0; sortArray[i]; ++i)
    {
        output[count[sortArray[i]]-1] = sortArray[i];
        --count[sortArray[i]];
        
    }
    for(int i = 0; sortArray[i]; ++i)
    {
        sortArray[i] = output[1];
    }
}

int getMax(int sortArray[], int arraySize)
{
    int max = sortArray[0];
    for(int i = 0; i < arraySize; i++)
    {
        if(sortArray[i] > max)
        {
            max = sortArray[i];
        }
    }
    return max;
}

void radixCount(int sortArray[], int arraySize, int digit)
{
    int output[arraySize];
    int count[10] = {0};

    for(int i = 0; i < arraySize; i++)
    {
        count[(sortArray[i]/digit)%10]++;
    }
    for(int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }
    for(int i = arraySize - 1; i >= 0; i--)
    {
        output[count[(sortArray[i]/digit)%10] - 1] = sortArray[i];
        count[(sortArray[i]/digit)%10]--;
    }
    for(int i = 0; i < arraySize; i++)
    {
        sortArray[i] = output[i];
    }
}

void radixSort(int sortArray[], int arraySize)
{
    int max = getMax(sortArray, arraySize);
    for(int digit = 1; max/digit > 0; digit *= 10)
    {
        radixCount(sortArray, arraySize, digit);
    }
}

void printArr(int sortArray[], int arraySize){
    for (int i = 0; i<=arraySize-1; i++){
        cout << sortArray[i];
    }
}

int main(){
    //srand(12);
    int arraySize = 1000;
    int x;
    int randArray[arraySize];
    int bubbleArray[arraySize];
    int insertArray[arraySize];
    int mergeArray[arraySize];
    int quickArray[arraySize];
    int countArray[arraySize];
    int radixArray[arraySize];
    //fill randArray with the values to be sorted
    for(int i = 0; i < arraySize; i++)
    {
        x = rand() % (2*(arraySize + 1));
        randArray[i] = x;
    }
    //copy randArray to the arrays for the different sorts
    for(int i = 0; i < arraySize; i++)
    {
        bubbleArray[i] = randArray[i];
        insertArray[i] = randArray[i];
        mergeArray[i] = randArray[i];
        quickArray[i] = randArray[i];
        countArray[i] = randArray[i];
        radixArray[i] = randArray[i];
    }
    auto t1 = Clock::now();
    bubbleSort(bubbleArray, arraySize);
    auto t2 = Clock::now();
    cout << "Bubble sort time with " << arraySize <<" entries:" << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds." << endl;
    
    t1 = Clock::now();
    insertionSort(insertArray, arraySize);
    t2 = Clock::now();
    cout << "Insertion sort time with " << arraySize <<" entries:" << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds." << endl;
    
    /* t1 = Clock::now();
    mergeSort(insertArray, 0, arraySize - 1);
    t2 = Clock::now();
    cout << "Merge sort time with " << arraySize <<" entries:" << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds." << endl; */

    t1 = Clock::now();
    quickSort(insertArray, 0, arraySize-1);
    t2 = Clock::now();
    cout << "Quick sort time with " << arraySize <<" entries:" << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds." << endl;

    t1 = Clock::now();
    countSort(insertArray, arraySize, 2*(arraySize + 1));
    t2 = Clock::now();
    cout << "Counting sort time with " << arraySize <<" entries:" << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds." << endl;

    t1 = Clock::now();
    radixSort(insertArray, arraySize);
    t2 = Clock::now();
    cout << "Radix sort time with " << arraySize <<" entries:" << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds." << endl;
    return 0;
}
