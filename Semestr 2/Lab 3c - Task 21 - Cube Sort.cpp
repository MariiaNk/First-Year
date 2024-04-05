#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#define NMAX 100000

using namespace std;
using namespace std::chrono;

const int CUBE_SIZE = 8;

// function to sort the cube
void cubeSort(int arr[], int n)
{
    // divide the array into cubes of size CUBE_SIZE 
    for (int i = 0; i < n; i += CUBE_SIZE)
    {
        std::sort(arr + i, arr + std::min(i + CUBE_SIZE, n));
    }

    // merge the cubes 
    int temp[n];
    for (int i = 0; i < n; i += CUBE_SIZE)
    {
        std::merge(arr + i, arr + std::min(i + CUBE_SIZE, n),
                   arr + std::min(i + CUBE_SIZE, n),
                   arr + std::min(i + 2*CUBE_SIZE, n),
                   temp + i);
    }
    // copy the result from temp[] back to arr[] 
    for (int i = 0; i < n; i++)
        arr[i] = temp[i];
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
    cubeSort(arr, n);
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

    outputArr(arr, n);
    int p = rand() % 5;
    copyArray(copy, arr, n);
    auto start = high_resolution_clock::now();
    cubeSort(copy, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by CUBE SORT:  " << duration.count() << " microseconds" << endl;
    outputArr(copy, n);

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