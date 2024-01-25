#include<iostream>
#include<string.h>
#include<vector>
#include <cmath>

using namespace std;

void outputArr(char * arr, int N, string name)
{
    cout << name;
    for(int i = 0; i < N; i++)
        cout << arr[i] << " ";

    cout << "\n";
}

void changeSigns(int order, char * signs, int len)
{
    int changeDegree = 1;
    for(int i = 0; i < len; i++, changeDegree *= 2)
    {
        if((order / changeDegree) % 2 == 0) signs[i] = '+';
        else signs[i] = '-';
    }
}
int main()
{
     setlocale (LC_CTYPE, "ukr");
    int arr[1000], len, Sum = 0;
    char signs[1000];


    cout << "Input length:\n";
    cin >> len;
    cout << "Input arr:\n";

    for(int i = 0; i < len; i++)
    {
        cin >> arr[i];
        signs[i] = '+';
        Sum += arr[i];
    }

    int maxChange = pow(2, len); // Макисмальна кількість перестановок знаків

    for(int i = 0; i < maxChange && Sum != 0 ; i++)
    {
        Sum = 0;
        // Зміна послідовності знаків
        if(i > 0)  changeSigns(i, signs, len);
        //outputArr(signs, len, "Sign:");

        //Рахуємо суму
        for(int j = 0; j < len; j++)
        {
            //cout << Sum << "[" <<signs[j] <<  arr[j] << "] -> ";
            if(signs[j] == '+')  Sum += arr[j];
            else Sum -= arr[j];
        }
    }

    // Виводи послідовність, якщо сума = 0
    if(Sum == 0)
    {
        for(int j = 0; j < len; j++)
        {
            //cout << signs[j] << arr[j];
            if(!(j == 0 && signs[j] == '+')) cout << signs[j];
            if(arr[j] < 0) cout << "(" << arr[j] << ")";
            else cout << arr[j];

        }
        cout << "=0";
    }
    else
    {
        cout << "Неможливо скласти рівняння. Спробуйте з новою послідовністю\n\n";
        main();
        return 0;
    }
}

/*
10
2 1 3 5 7 9 6 4 8 1
-2+1+3-5-7-9+6+4+8+1=0


7
23 16 30 7 8 4 10
23+16-30-7-8-4+10=0

6
17 -8 7 14 -1 -3
17-(-8)-7-14+(-1)+(-3)=0

3
58 9 -60
-----
*/
