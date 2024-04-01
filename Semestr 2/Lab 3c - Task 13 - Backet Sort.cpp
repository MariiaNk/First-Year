//numbers 0 - 100
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>
#define NMAX 100000

using namespace std;
using namespace std::chrono;

void insertionSort(vector<int>& bucket) 
{
    for (int i = 1; i < bucket.size(); ++i) 
    {
        int key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) 
        {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

int maxValueInArray(int *arr, int n)
{
    int etalon = arr[0];
    for(int i = 1; i < n; i++)
    {
        if(arr[i] > etalon)
            etalon = arr[i];
    }
    return etalon;
}
void bucketSort(int* arr, int n)
{
    vector<int> b[n];
    int M = maxValueInArray(arr, n) + 1;
    for (int i = 0; i < n; i++) 
    {
        int bi = floor(n * arr[i] / M);
        b[bi].push_back(arr[i]);
    }

    for (int i = 0; i < n; i++) 
        insertionSort(b[i]);

    int index = 0;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < b[i].size(); j++) 
            arr[index++] = b[i][j];
        
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
    int arr[] = {35, 901, 68, 13, 14, 67, 87, 98, 150, 890, 650, 651};
    int n = 12; 

    outputArr(arr, n);
    cout << "***  BUCKET SORT  ***\n";
    bucketSort(arr, n);
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
        arr[i] = rand() % 1000 ;

    copyArray(copy, arr, n);
    auto start = high_resolution_clock::now();
    bucketSort(copy, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by BACKET SORT:  " << duration.count() << " microseconds" << endl;

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