#include <iostream>
#define NMAX 1000
using namespace std;

struct tSort
{
    string value;

    bool operator > (const tSort& other) const
    {
        if(value.size() == other.value.size()) 
        {
            for(int i = 0; i < value.size(); i++)
                if(value[i] != other.value[i])
                    return value[i] > other.value[i];
            return true;
        }
        return value.size() > other.value.size();
    }
};

void insertionSort(tSort *arr, int n)
{
    int j;
    tSort current; 
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
void outputArr(const tSort *arr, int n)
{
    cout << "==== ARRAY ====" << endl;
    for(int i = 0; i < n; i++)
        cout << arr[i].value << " ";
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
    tSort arr[10] = {"abbc", "cbba", "b", "hsaj", "lala", "ab",  "zy", "xyz", "ababagalamaga", "uhuuu"};
    int n = 10;

    outputArr(arr, n);
    cout << "***  INSERTION SORT  ***\n [Process is going...]\n";
    insertionSort(arr, n);
    outputArr(arr, n);

    arr[10] = {"abbc", "cbba", "b", "hsaj", "lala", "ab",  "zy", "xyz", "ababagalamaga", "uhuuu"};
}
void BenchmarkMode()
{
    tSort arr[NMAX];
    int n;
    cout << "Enter count of element: ";
    cin >> n;

    for(int i = 0; i < n; i++)
        arr[i].value = GenerateString();

    

}
int main()
{
    cout << "Input mode of work\nd - demonstration\nb - benchmark\n";
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