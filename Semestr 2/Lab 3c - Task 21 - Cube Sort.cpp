#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#define NMAX 100000

using namespace std;
using namespace std::chrono;


int custom_log2(int x)
{
    int res = 0;
    while (x >>= 1) res++;
    return res;
}

void insertionSort(int *arr, int size)
{
    for (int i = 1; i < size; ++i) 
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int *arr1, int *arr2, int size1, int size2) 
{
    int merged[size1 + size2];
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) 
    {
        if (arr1[i] <= arr2[j])
            merged[k++] = arr1[i++];
        else
            merged[k++] = arr2[j++];
    }
    while (i < size1)
        merged[k++] = arr1[i++];

    while (j < size2)
        merged[k++] = arr2[j++];

    for (int m = 0; m < size1 + size2; m++)
        arr1[m] = merged[m];
}

void cubeSort(int *arr, int n, int p)
{
    int subarraySize = n / p;
    int subarray[subarraySize];

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < subarraySize; j++)
            subarray[j] = arr[i * subarraySize + j];

        insertionSort(subarray, subarraySize);

        for (int k = 0; k < custom_log2(p); k++) {
            int partner = i ^ (1 << k);
            int buffer[subarraySize];
            for (int j = 0; j < subarraySize; j++)
                buffer[j] = arr[partner * subarraySize + j];

            if (i < partner)
                merge(subarray, buffer, subarraySize, subarraySize);
            else
                merge(buffer, subarray, subarraySize, subarraySize);
        }

        for (int j = 0; j < subarraySize; j++)
            arr[i * subarraySize + j] = subarray[j];
    }
}
void outputArr(const int *arr, int n)
{
    cout << "==== ARRAY ====" << endl;
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void DemonstrationMode()
{
    int arr[] = {5, 8, 2, 3, 1, 6, 9, 7, 4};
    int n = 9;
    
    outputArr(arr, n);
    cout << "***  CUBE SORT  ***\n";
    cubeSort(arr, n, 2);
    outputArr(arr, n);
    cout << endl;
    
}

void copyArray(int *str1, const int *str2, int n)
{
    for (int i = 0; i < n; ++i) 
        str1[i] = str2[i];
}

void BenchmarkMode()
{
    int arr[NMAX], copy[NMAX];
    int n;
    cout << "Enter count of element: ";
    cin >> n;

    for(int i = 0; i < n; i++)
        arr[i] = rand() % 100;

    //outputArr(arr, n);
    int p = rand() % 5;
    copyArray(copy, arr, n);
    auto start = high_resolution_clock::now();
    cubeSort(copy, n, p);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by CUBE SORT:  " << duration.count() << " microseconds" << endl;
    //outputArr(copy, n);

    copyArray(copy, arr, n);
    start = high_resolution_clock::now();
    sort(copy, copy + n);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by STANDART SORT:  " << duration.count() << " microseconds" << endl;

}


int main() 
{
    srand(0);
    cout << "Input mode of work\nd - demonstration\nb - benchmark\n";
    cout << "Enter request:";
    char mode;
    cin >> mode;
    if(mode == 'd')
        DemonstrationMode();
    else if(mode == 'b')
        BenchmarkMode();
    else
    {
        cout << "Error. Program isn't started\n";
        return 1;
    }
    return 0;
}