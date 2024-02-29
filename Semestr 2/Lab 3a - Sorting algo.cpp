#include <iostream>
#include <algorithm>
#include <chrono>
const int NMAX = 1e3;

using namespace std;
using namespace std::chrono;

bool operator>(const string& str1, const string& str2) 
{
    if(str1.size() == str2.size()) 
    {
        for(int i = 0; i < str1.size(); i++)
            if(str1[i] != str2[i])
                return str1[i] > str2[i];
        return false;
    }
    return str1.size() > str2.size();
}

bool operator>=(const string& str1, const string& str2) 
{
    if(str1.size() == str2.size()) 
    {
        for(int i = 0; i < str1.size(); i++)
            if(str1[i] != str2[i])
                return str1[i] > str2[i];
        return true;
    }
    return str1.size() > str2.size();
}

void copyArray(string *str1, const string *str2, int n)
{
    for (int i = 0; i < n; ++i) 
        str1[i] = str2[i];
}

void insertionSort(string *arr, int n)
{
    int j;
    string current; 
    //move element and pointer
    for(int i = 0; i < n; i++)
    {
        current = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > current)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
}
int partQuickSort(string *arr, int st, int fn)
{
    int idRandom = st + rand() % (fn - st);
    swap(arr[idRandom], arr[fn]);
    string pivot = arr[fn];
    int i = st - 1;
    for(int j = st; j < fn; j++)
    {
        if(pivot >= arr[j])
        {
            i++;
            swap(arr[j], arr[i]);
        }
    }
    swap(arr[i+1], arr[fn]);
    return i+1;

}
void quickSort(string *arr, int st, int fn)
{
    if(st < fn)
    {
        int middle = partQuickSort(arr, st, fn);
        quickSort(arr, st, middle - 1);
        quickSort(arr, middle + 1, fn);
    }
}

void merge(string *arr, int st, int mid, int fn)
{
    int i, j, k;
    int n1 = mid - st + 1;
    int n2 = fn - mid;

    string L[n1], R[n2]; 
    for (i = 0; i < n1; i++)
        L[i] = arr[st + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1+ j];
    i = j = 0;
    k = st;
    while (i < n1 && j < n2)
    {
        if (R[j] >= L[i])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(string *arr, int n)
{ 
    for (int i = 1; i <= n - 1; i *= 2) // current Size
        for (int j = 0; j < n-1; j += 2*i) // start of sub array
        {
            int middle = min(j + i - 1, n-1);
            int rEnd = min(j + 2*i - 1, n-1);
            merge(arr, j, middle, rEnd);
        }
}

void combineSort(string *arr, int n)
{
    if(n > 100) 
    {
        //cout << "Big..." << endl;
        quickSort(arr, 0, n - 1);
    }
    else 
    {
        //cout << "Small..." << endl;
        insertionSort(arr, n);
    }
}
void outputArr(const string *arr, int n)
{
    cout << "==== ARRAY ====" << endl;
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
string GenerateString()
{
    string availableSymb = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", str;
    int sizeSymb = availableSymb.size();
    int n = rand()%7 + 2;
    int symbId;
    for(int i = 0; i < n; i++)
    {
        symbId = rand() % (sizeSymb-1);
        str += availableSymb[symbId];
    }
    return str;
}

bool cmp(string a, string b)
{
    return b > a;
}

void DemonstrationMode()
{
    string arr[10] = {"abbc", "cbba", "b", "hsaj", "lala", "ab",  "zy", "xyz", "ababagalamaga", "uhuuu"};
    string copy[10];
    int n = 10;

    copyArray(copy, arr, n);
    outputArr(copy, n);
    cout << "***  INSERTION SORT  ***\n";
    insertionSort(copy, n);
    outputArr(copy, n);
    cout << endl;

    copyArray(copy, arr, n);
    outputArr(copy, n);
    cout << "***  QUICK SORT  ***\n";
    quickSort(copy, 0, n - 1);
    outputArr(copy, n);
    cout << endl;

    copyArray(copy, arr, n);
    outputArr(copy, n);
    cout << "***  MERGE SORT  ***\n";
    mergeSort(copy, n);
    outputArr(copy, n);
    cout << endl;

    copyArray(copy, arr, n);
    outputArr(copy, n);
    cout << "***  COMBINE SORT [QUICK/INSERTION]  ***\n";
    combineSort(copy, n);
    outputArr(copy, n);
    cout << endl;

    copyArray(copy, arr, n);
    outputArr(copy, n);
    cout << "***  STANDARD SORT  ***\n";
    sort(copy,  copy + n, cmp);
    outputArr(copy, n);
    cout << endl;
}

void BenchmarkMode()
{
    string arr[NMAX], copy[NMAX];
    int n;
    cout << "Enter count of element: ";
    cin >> n;

    for(int i = 0; i < n; i++)
        arr[i] = GenerateString();

    copyArray(copy, arr, n);
    auto start = high_resolution_clock::now();
    insertionSort(copy, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by INSERTION SORT:  " << duration.count() << " microseconds" << endl;

    copyArray(copy, arr, n);
    start = high_resolution_clock::now();
    quickSort(copy, 0, n - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by QUICK SORT:  " << duration.count() << " microseconds" << endl;

    copyArray(copy, arr, n);
    start = high_resolution_clock::now();
    mergeSort(copy, n);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by MERGE SORT:  " << duration.count() << " microseconds" << endl;

    copyArray(copy, arr, n);
    start = high_resolution_clock::now();
    combineSort(copy, n);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by COMBINE SORT:  " << duration.count() << " microseconds" << endl;

    copyArray(copy, arr, n);
    start = high_resolution_clock::now();
    sort(arr, arr+n, cmp);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by STANDARD SORT:  " << duration.count() << " microseconds" << endl;
    

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