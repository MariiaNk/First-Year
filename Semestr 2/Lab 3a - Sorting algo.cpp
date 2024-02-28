#include <iostream>
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


void DemonstrationMode()
{
    string arr[10] = {"abbc", "cbba", "b", "hsaj", "lala", "ab",  "zy", "xyz", "ababagalamaga", "uhuuu"};
    string copy[10];
    int n = 10;

    copyArray(copy, arr, n);
    outputArr(copy, n);
    cout << "***  INSERTION SORT  ***\n [Process is going...]\n";
    insertionSort(copy, n);
    outputArr(copy, n);

    copyArray(copy, arr, n);
    outputArr(copy, n);
    cout << "***  QUICK SORT  ***\n [Process is going...]\n";
    quickSort(copy, 0, n - 1);
    outputArr(copy, n);
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
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by INSERTION SORT:  " << duration.count() << " milliseconds" << endl;

    copyArray(copy, arr, n);
    start = high_resolution_clock::now();
    quickSort(copy, 0, n - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by QUICK SORT:  " << duration.count() << " milliseconds" << endl;
    

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