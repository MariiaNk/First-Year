#include <iostream>
#include <vector>
#include <chrono>
#define NMAX 100000

using namespace std;
using namespace std::chrono;

void insertionSort(vector<float>& bucket) 
{
    for (int i = 1; i < bucket.size(); ++i) 
    {
        float key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) 
        {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

void bucketSort(float arr[], int n)
{
    vector<float> b[n];

    for (int i = 0; i < n; i++) 
    {
        int bi = n * arr[i];
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

void outputArr(const float *arr, int n)
{
    cout << "==== ARRAY ====" << endl;
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void DemonstrationMode()
{
    float arr[] = {0.3465, 0.632, 0.667, 0.565, 0.1253, 0.667, 0.888 };
    int n = 7; 

    outputArr(arr, n);
    cout << "***  BUCKET SORT  ***\n";
    bucketSort(arr, n);
    outputArr(arr, n);
    cout << endl;
    
}

void BenchmarkMode()
{
    float arr[NMAX];
    int n;
    cout << "Enter count of element (<10000): ";
    cin >> n;

    for(int i = 0; i < n; i++)
        arr[i] = rand() % 1000;

    auto start = high_resolution_clock::now();
    bucketSort(arr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by BACKET SORT:  " << duration.count() << " microseconds" << endl;
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